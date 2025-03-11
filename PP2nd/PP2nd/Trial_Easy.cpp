#include "Trial_Easy.h"
#include "MainScreen.h"

Trial_Easy::Trial_Easy()
{
	std::thread loader1([] {GameM().Load("Trial_Easy.txt"); });
	std::thread loader3([] {EffectM().Load(Down); });
	std::thread loader4([] {AudioM().Load(Main); });

	loader1.join();
	/// EnemyManagerでGameManagerのデータにアクセスするため、待機する
	std::thread loader2([] {EnemyM().LoadTest(); });
	loader2.join();
	loader3.join();
	loader4.join();

	mainScreenUPtr = std::make_unique<MainScreen>();
	mainScreenUPtr->Init(GameM().GetMapInfo());

	AudioM().PlayBGM(BGMList::SETUP);
	EnemyM().Setrevision(10);
	GameM().GameStart();
}

Trial_Easy::~Trial_Easy()
{
}

void Trial_Easy::Update() const
{
#if _DEBUG
	// DrawFormatString(0, 0, 65535, "展示シーン１");
	EnemyM().DrawRouteTest();
#endif
	mainScreenUPtr->Update();
}
