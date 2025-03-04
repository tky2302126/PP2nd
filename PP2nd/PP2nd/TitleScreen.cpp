#include "TitleScreen.h"


void TitleScreen::Init()
{
	cameraUPtr = std::make_unique<Camera>();
	hudUPtr = std::make_unique<HUD>();
	mapUPtr = std::make_unique<Map>();

	hudUPtr->SetCallback([&](TerrainList name) {mapUPtr->RegistHoldItem(name); });
	
	cameraUPtr->Init();
	hudUPtr->Init(Title);
	mapUPtr->Init();
	
	oldSequence = currentSequence;
	titleLogoGH = LoadGraph("./Resource/titlelogo.png");

	Button* stageButton = new Button();
	RECTInt ButtonPos =
	{
		WINDOW_HEIGHT / 2 - BUTTON_HEIGHT / 2,
		WINDOW_HEIGHT / 2 + BUTTON_HEIGHT / 2,
		WINDOW_WIDTH / 8 * 7 - BUTTON_WIDTH / 2,
		WINDOW_WIDTH / 8 * 7 + BUTTON_WIDTH / 2,

	};
	std::string text = "Easy";
	int hovercolor = GetColor(100, 100, 255);
	int normalColor = GetColor(0, 0, 0);
	stageButton->Init(ButtonPos, hovercolor, normalColor, text, [&]() {OnPressStageButton(); });
	menuButtonPtrVec.push_back(stageButton);
}

void TitleScreen::UnInit()
{
	DeleteGraph(titleLogoGH);
	if(!menuButtonPtrVec.empty())
	{
		for(auto& ButtonPtr : menuButtonPtrVec)
		{
			if (ButtonPtr != nullptr) 
			{
				delete ButtonPtr; 
				ButtonPtr = nullptr;
			}
		}

		menuButtonPtrVec.clear();
	}
	cameraUPtr->UnInit();
	hudUPtr->UnInit();
	mapUPtr->UnInit();
}

void TitleScreen::Draw()
{
	if (!isActive) return;
	hudUPtr->Update();
	mapUPtr->Update(currentSequence);

#pragma region タイトル画面の操作説明
	if(currentSequence == Title)
	{
		DrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3,GetColor(255, 255, 255),"石を置け");
		DrawFormatString(WINDOW_WIDTH / 4 * 3, WINDOW_HEIGHT / 6 * 5,GetColor(255, 255, 255),"右クリック長押しでスキップ");

	}
#pragma endregion

	/// タイトルからメニュー画面に移行する時
	if (oldSequence == Title && currentSequence == Menu)
	{
		MoveCamera(); // カメラ移動指示
		oldSequence = currentSequence;
	}

#pragma region メニュー画面のUI描画
	/// 画面右側にoptionを表示
	/// ボタンのようにしたいのでrectでホバーを実装
	/// 左クリックでシーン遷移
	if(currentSequence == Menu && !isMoving)
	{
		if(!menuButtonPtrVec.empty())
		{
			for(int i=0; i < menuButtonPtrVec.size();i++)
			{
				menuButtonPtrVec[i]->Update();
			}
		}
	}
#pragma endregion

}

void TitleScreen::Update()
{
	/// シーン遷移
	if (!isActive)
	{
		UnInit();
		SM().ChangeScene(nextScene);
		return;
	}
	cameraUPtr->Update(currentSequence);
	Draw();
	
	auto mouseInfo = Input().GetMouseInfo();
#if _DEBUG
	/// clsDx();
	/// printfDx("タイトルシーン");
	/// printfDx("シーケンス : %d", currentSequence);
	if(CheckHitKey(KEY_INPUT_C))
	{
		currentSequence = Menu;
	}
#endif
#pragma region タイトル画面スキップ
	/// 右クリック長押しでスキップできる
	if(currentSequence == Title)
	{
		if (mouseInfo.state.right == Started) { pressStart = GetNowCount(); }

		if (mouseInfo.state.right == Canceled) { pressStart = 0; }

		if(mouseInfo.state.right == Performed)
		{
			int elapsedTime = GetNowCount() - pressStart;
			if(elapsedTime >= holdThreshold * 1000)
			{
				currentSequence = Menu;
			}
		}
	}
#pragma endregion

	/// カメラ移動
	/// タイトルロゴ遷移(この後実装)
	if(isMoving && isActive)
	{
		elapsedTime += 1.0 / FRAMERATE;
		float t = elapsedTime / moveDuration;
		if(t >= 1.0f)
		{
			t = 1.0;
			isMoving = false;
			AM().PlayBGM(TITLE);
		}

		VECTOR currentPos = VGet(
			startPos.x + (endPos.x - startPos.x) * t,
			startPos.y + (endPos.y - startPos.y) * t,
			startPos.z + (endPos.z - startPos.z) * t
		);

		VECTOR currentTarget = VGet(
			startTarget.x + (endTarget.x - startTarget.x) * t,
			startTarget.y + (endTarget.y - startTarget.y) * t,
			startTarget.z + (endTarget.z - startTarget.z) * t
		);

		RECTInt currentLogo =
		{
			logoStart.top +(logoEnd.top - logoStart.top) * t,
			logoStart.bottom + (logoEnd.bottom - logoStart.bottom) * t,
			logoStart.left,
			logoStart.right
		};

		cameraUPtr->ManualMove(currentPos, currentTarget);
		DrawExtendGraph(currentLogo.left, currentLogo.top, currentLogo.right, currentLogo.bottom, titleLogoGH, FALSE);
	}

	/// タイトルロゴ描画
	if(currentSequence == Menu && !isMoving)
	{
		DrawExtendGraph(logoEnd.left, logoEnd.top, logoEnd.right, logoEnd.bottom, titleLogoGH, FALSE);
	}
	
}

void TitleScreen::MoveCamera()
{
	startPos = CAMERA_START_POS;
	startTarget = CAMERA_START_TARGET;

	endPos = CAMERA_END_POS;
	endTarget = CAMERA_END_TARGET;

	isMoving = true;
}

/// <summary>
/// シーン遷移予約処理
/// </summary>
void TitleScreen::OnPressStageButton()
{
	isActive = false;
	nextScene = Main;
}
