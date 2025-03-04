#include "MainScreen.h"

/// <summary>
/// 適当なマップサイズを指定して描画する
/// </summary>
/// <param name="mapInfo"></param>
void MainScreen::Init(const _mapInfo& mapInfo)
{
	cameraUPtr = std::make_unique<Camera>();
	hudUPtr = std::make_unique<HUD>();
	mapUPtr = std::make_unique<Map>();
	cameraUPtr->Init(mapInfo);
	hudUPtr->Init();
	mapUPtr->Init(mapInfo);
	hudUPtr->SetCallback([&](TerrainList name) {mapUPtr->RegistHoldItem(name); });
	stageClearGH = LoadGraph("./Resource/stageclear.png");
	gameOverGH = LoadGraph("./Resource/gameover.jpg");
}

void MainScreen::UnInit()
{
	cameraUPtr->UnInit();
	hudUPtr->UnInit();
	mapUPtr->UnInit();
	DeleteGraph(stageClearGH);
	DeleteGraph(gameOverGH);
}

void MainScreen::Draw()
{
	// ゲームクリア時のスプライト
	if (GameM().IsGameClear())
	{ DrawExtendGraph(20, WINDOW_HEIGHT / 4, WINDOW_WIDTH - 20, WINDOW_HEIGHT/4*3, stageClearGH, FALSE);}
	// ゲームオーバー時のスプライト
	if(GameM().IsGameOver())
	{DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, gameOverGH, FALSE);}
	
}

/// <summary>
/// todo map と hudのout of boundsの設定
/// </summary>
void MainScreen::Update()
{
	Draw();
	cameraUPtr->Update();
	mapUPtr->Update();
	int time = TimeManager::GetInstance().RemainTime();
	hudUPtr->Update(time);
#pragma region カメラ確認
	// VECTOR cameraPos = cameraUPtr->GetPosition();
	// DrawFormatString(0, 30, GetColor(255, 255, 255), "camera position( %f, %f, %f)",cameraPos.x , cameraPos.y , cameraPos.z);
#pragma endregion
}

