#include "Trial_Easy.h"
#include "MainScreen.h"

Trial_Easy::Trial_Easy()
{
	std::thread loader1([] {GM().Load("Trial_Easy.txt"); });
	std::thread loader4([] {AM().Load(Main); });

	loader1.join();
	/// EnemyManagerでGameManagerのデータにアクセスするため、待機する
	std::thread loader2([] {EM().LoadTest(); });
	loader2.join();
	loader4.join();

	mainScreenUPtr = std::make_unique<MainScreen>();
	mainScreenUPtr->Init(GM().GetMapInfo());

	AM().PlayBGM(BGMList::SETUP);
	EM().Setrevision(10);
	GM().GameStart();
}

Trial_Easy::~Trial_Easy()
{
}

void Trial_Easy::Update() const
{
#if _DEBUG
	// DrawFormatString(0, 0, 65535, "展示シーン１");
	EM().DrawRouteTest();
#endif
	mainScreenUPtr->Update();
}
