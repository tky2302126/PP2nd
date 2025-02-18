#include "MainScreen.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"

/// <summary>
/// 適当なマップサイズを指定して描画する
/// </summary>
/// <param name="mapInfo"></param>
void MainScreen::Init(const _mapInfo& mapInfo)
{
	cameraUPtr = make_unique<Camera>();
	hudUPtr = make_unique<HUD>();
	mapUPtr = make_unique<Map>();
	cameraUPtr->Init(mapInfo);
	hudUPtr->Init();
	mapUPtr->Init(mapInfo);
	hudUPtr->SetCallback([&](TerrainList name) {mapUPtr->RegistHoldItem(name); });
	stageClearGH = LoadGraph("./Resource/stageclear.png");
	gameOverGH = LoadGraph("./Resource/gameover.jpg");
}

/// <summary>
/// csvでデータを読み込む
/// </summary>
/// <param name="day"></param>
void MainScreen::Init(const int day)
{
	cameraUPtr = make_unique<Camera>();
	hudUPtr = make_unique<HUD>();
	mapUPtr = make_unique<Map>();
	_mapInfo mapInfo = _mapInfo() /*GetMapInfo(day)*/;
	cameraUPtr->Init(mapInfo);
	hudUPtr->Init();
	mapUPtr->Init(mapInfo);
	hudUPtr->SetCallback([&](TerrainList name) {mapUPtr->RegistHoldItem(name); });
}

void MainScreen::UnInit()
{
	cameraUPtr->UnInit();
	hudUPtr->UnInit();
	mapUPtr->UnInit();
}

void MainScreen::Draw()
{
	if (GameManager::GetInstance().IsGameClear()) 
	{ DrawExtendGraph(20, WINDOW_HEIGHT / 4, WINDOW_WIDTH - 20, WINDOW_HEIGHT/4*3, stageClearGH, FALSE);}
	if(GameManager::GetInstance().IsGameOver())
	{DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, gameOverGH, FALSE);}
	mapUPtr->Update();
	int time = TimeManager::GetInstance().RemainTime();
	hudUPtr->Update(time);
}

/// <summary>
/// todo map と hudのout of boundsの設定
/// </summary>
void MainScreen::Update()
{
	Draw();
	cameraUPtr->Update();
#pragma region カメラ確認
	// VECTOR cameraPos = cameraUPtr->GetPosition();
	// DrawFormatString(0, 30, GetColor(255, 255, 255), "camera position( %f, %f, %f)",cameraPos.x , cameraPos.y , cameraPos.z);
#pragma endregion
}

