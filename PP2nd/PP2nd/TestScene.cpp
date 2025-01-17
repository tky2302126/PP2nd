#include "TestScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"
#include "Box.h"
#include "MyMath.h"
#include "MainScreen.h"

TestScene::TestScene()
{
	cameraPtr = new Camera();
	cameraPtr->Init();
	hudUPtr = make_unique<HUD>();
	hudUPtr->Init();
	mapUPtr = make_unique<Map>();
	mapUPtr->Init();

	mainScreenUPtr = make_unique<MainScreen>();
	_mapInfo testMap(12,9,5,5);
	mainScreenUPtr->Init(testMap);
}

TestScene::~TestScene()
{
	cameraPtr->UnInit();
	delete cameraPtr;
}

void TestScene::Update()
{
	DrawFormatString(0, 0, 65535, " テストシーン");
	InputSystem::GetInstance().Update();
#pragma region マウス確認
	/// MouseInfo mouseInfo = InputSystem::GetInstance().GetMouseInfo();
	/// 
	/// DrawFormatString(0, 30, GetColor(255, 255, 255), "mouse position( %d, %d)", mouseInfo.position.x, mouseInfo.position.y);
	/// DrawFormatString(0, 60, GetColor(255, 255, 255), "mouse state( %d , %d)",mouseInfo.state.left,mouseInfo.state.right );
#pragma endregion


#pragma region カメラ確認
	
	/// VECTOR cameraPos = cameraPtr->GetPosition();
	/// 
	/// DrawFormatString(0, 30, GetColor(255, 255, 255), "camera position( %f, %f, %f)",cameraPos.x , cameraPos.y , cameraPos.z);
#pragma endregion
#pragma region メインスクリーンテスト
	mainScreenUPtr->Update();
#pragma endregion

}
