#include "TestScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"
#include "Box.h"
#include "MainScreen.h"

TestScene::TestScene()
{
	/// 
	GameManager::GetInstance().LoadTest();
	EnemyManager::GetInstance().LoadTest();
	TimeManager::GetInstance().LoadTest();
	AudioManager::GetInstance().LoadTest();

	mainScreenUPtr = std::make_unique<MainScreen>();
	mainScreenUPtr->Init(GameManager::GetInstance().GetMapInfo());

	AudioManager::GetInstance().PlayBGM(BGMList::SETUP);
}

TestScene::~TestScene()
{
}

void TestScene::Update() const 
{
	DrawFormatString(0, 0, 65535, " テストシーン");
#pragma region マウス確認
	/// MouseInfo mouseInfo = InputSystem::GetInstance().GetMouseInfo();
	/// 
	/// DrawFormatString(0, 30, GetColor(255, 255, 255), "mouse position( %d, %d)", mouseInfo.position.x, mouseInfo.position.y);
	/// DrawFormatString(0, 60, GetColor(255, 255, 255), "mouse state( %d , %d)",mouseInfo.state.left,mouseInfo.state.right );
#pragma endregion

#pragma region メインスクリーンテスト
	mainScreenUPtr->Update();
	EnemyManager::GetInstance().DrawRouteTest();
#pragma endregion
	if(CheckHitKey(KEY_INPUT_E)&& GameManager::GetInstance().CurrentSequence() == Debug)
	{
		//GameManager::GetInstance().ExportStageInfo("Test.txt");
		EnemyManager::GetInstance().SpawnEnemyTest();
	}

}
