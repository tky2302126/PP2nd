#include "MainScreen.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"

void MainScreen::Init(const _mapInfo& mapInfo)
{
	cameraUPtr = make_unique<Camera>();
	hudUPtr = make_unique<HUD>();
	mapUPtr = make_unique<Map>();
	cameraUPtr->Init();
	hudUPtr->Init();
	mapUPtr->Init(mapInfo);
}

void MainScreen::UnInit()
{
	cameraUPtr->UnInit();
	hudUPtr->UnInit();
	mapUPtr->UnInit();
}

void MainScreen::Draw()
{
	mapUPtr->Update();
	hudUPtr->Update();
}

/// <summary>
/// todo map と hudのout of boundsの設定
/// </summary>
void MainScreen::Update()
{
	Draw();
	cameraUPtr->Update();
#pragma region カメラ確認
	VECTOR cameraPos = cameraUPtr->GetPosition();
	DrawFormatString(0, 30, GetColor(255, 255, 255), "camera position( %f, %f, %f)",cameraPos.x , cameraPos.y , cameraPos.z);
#pragma endregion
}
