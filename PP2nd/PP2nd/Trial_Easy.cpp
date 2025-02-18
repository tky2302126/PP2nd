#include "Trial_Easy.h"
#include "MainScreen.h"

Trial_Easy::Trial_Easy()
{
	mainScreenUPtr = make_unique<MainScreen>();
	mainScreenUPtr->Init(GameManager::GetInstance().GetMapInfo());

	AudioManager::GetInstance().PlayBGM(BGMList::SETUP);
}

Trial_Easy::~Trial_Easy()
{
}

void Trial_Easy::Update() const
{
#if _DEBUG
	DrawFormatString(0, 0, 65535, "“WŽ¦ƒV[ƒ“‚P");
	EnemyManager::GetInstance().DrawRouteTest();
#endif
	mainScreenUPtr->Update();
}
