#include "Trial_Easy.h"
#include "MainScreen.h"

Trial_Easy::Trial_Easy()
{
	mainScreenUPtr = std::make_unique<MainScreen>();
	mainScreenUPtr->Init(GM().GetMapInfo());

	AM().PlayBGM(BGMList::SETUP);
}

Trial_Easy::~Trial_Easy()
{
}

void Trial_Easy::Update() const
{
#if _DEBUG
	DrawFormatString(0, 0, 65535, "“WŽ¦ƒV[ƒ“‚P");
	EM().DrawRouteTest();
#endif
	mainScreenUPtr->Update();
}
