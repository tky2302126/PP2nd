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


	/// buttonGH = LoadGraph();
	/// confirmGH = LoadGraph();
	/// arrowImageGH = LoadGraph();
	
	oldSequence = currentSequence;
}

void TitleScreen::UnInit()
{

}

void TitleScreen::Draw()
{
	hudUPtr->Update();
	mapUPtr->Update(currentSequence);

#pragma region タイトル画面の操作説明
	if(currentSequence == Title)
	{
		DrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3,GetColor(255, 255, 255),"石を置け");
	}
#pragma endregion

	/// タイトルからメニュー画面に移行する時
	if (oldSequence == Title && currentSequence == Menu)
	{
		
		oldSequence = currentSequence;
	}

#pragma region メニュー画面のUI描画
	if(currentSequence == Menu)
	{
		
	}
#pragma endregion

}
/// <summary>
/// 操作方法を字幕で表示
/// 置いたとき、カメラを引き全体像を表示する
/// タイトルロゴを表示
/// クリックでメニュー画面へ遷移 -> なくなりそう
/// </summary>
void TitleScreen::Update()
{
	clsDx();
	Draw();
	cameraUPtr->Update(currentSequence);
	auto mouseInfo = Input().GetMouseInfo();
	printfDx("タイトルシーン");
	printfDx("シーケンス : %d", currentSequence);
#if _DEBUG
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

	
}
