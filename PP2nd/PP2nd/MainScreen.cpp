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
/// todo map ‚Æ hud‚Ìout of bounds‚Ìİ’è
/// </summary>
void MainScreen::Update()
{
	Draw();
	cameraUPtr->Update();
}
