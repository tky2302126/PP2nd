#include "TestScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"
#include "Box.h"
#include "MainScreen.h"

TestScene::TestScene()
{
	int startTime = GetNowCount();
	std::thread loader1([] {GameM().LoadTest(); });
	std::thread loader3([] {TimeM().LoadTest(); });
	std::thread loader4([] {AudioM().LoadTest(); });
	std::thread loader5([] {EffectM().Load(Down); });

	loader1.join();
	/// EnemyManagerでGameManagerのデータにアクセスするため、待機する
	std::thread loader2([] {EnemyM().LoadTest(); });
	loader2.join();
	loader3.join();
	loader4.join();
	loader5.join();
	
	int elapsedTime = GetNowCount() - startTime;
	elapsedTime /= 1000;
	printfDx("かかった時間 : %d", elapsedTime);

	mainScreenUPtr = std::make_unique<MainScreen>();
	mainScreenUPtr->Init(GameM().GetMapInfo());

	AudioM().PlayBGM(BGMList::SETUP);
}

TestScene::~TestScene()
{
}

void TestScene::Update() const 
{
	DrawFormatString(0, 0, 65535, " テストシーン");
#pragma region マウス確認
	/// MouseInfo mouseInfo = Input().GetMouseInfo();
	/// 
	/// DrawFormatString(0, 30, GetColor(255, 255, 255), "mouse position( %d, %d)", mouseInfo.position.x, mouseInfo.position.y);
	/// DrawFormatString(0, 60, GetColor(255, 255, 255), "mouse state( %d , %d)",mouseInfo.state.left,mouseInfo.state.right );
#pragma endregion

#pragma region メインスクリーンテスト
	mainScreenUPtr->Update();
	EnemyManager::GetInstance().DrawRouteTest();
#pragma endregion
	if(CheckHitKey(KEY_INPUT_E)&& CGameM().CurrentSequence() == Debug)
	{
		//GameManager::GetInstance().ExportStageInfo("Test.txt");
		// EnemyManager::GetInstance().SpawnEnemyTest();
		EffectM().Play(Down, VGet(0, 0, 0), 1.0);
	}

}
