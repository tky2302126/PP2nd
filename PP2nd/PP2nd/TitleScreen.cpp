#include "TitleScreen.h"


void TitleScreen::Init()
{
	cameraUPtr = std::make_unique<Camera>();
	hudUPtr = std::make_unique<HUD>();
	mapUPtr = std::make_unique<Map>();

	cameraUPtr->Init();
	hudUPtr->Init();
	mapUPtr->Init();

	/// buttonGH = LoadGraph();
	/// confirmGH = LoadGraph();
	/// arrowImageGH = LoadGraph();
}

void TitleScreen::UnInit()
{

}

void TitleScreen::Draw()
{
	hudUPtr->Update();
	mapUPtr->Update(currentSequence);
}
/// <summary>
/// 近いカメラで配置場所を示す
/// 操作方法を字幕で表示
/// 置いたとき、カメラを引き全体像を表示する
/// 右クリック長押しでスキップできる(できれば実装)
/// タイトルロゴを表示
/// クリックでメニュー画面へ遷移
/// </summary>
void TitleScreen::Update()
{
	Draw();
	cameraUPtr->Update(currentSequence);
#if _DEBUG
	if(CheckHitKey(KEY_INPUT_C))
	{
		currentSequence = Menu;
	}
#endif
}
