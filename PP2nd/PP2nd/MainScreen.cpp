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
/// todo map �� hud��out of bounds�̐ݒ�
/// </summary>
void MainScreen::Update()
{
	Draw();
	cameraUPtr->Update();
}
