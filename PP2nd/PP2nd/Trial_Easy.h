#pragma once
#include "Scene.h"
#include "define.h"
#include "manager.h"

class MainScreen;
class Trial_Easy :public Scene
{
public:
	Trial_Easy();
	~Trial_Easy();

	void Update() const override;

private:
	UniquePtr<MainScreen> mainScreenUPtr;
};

