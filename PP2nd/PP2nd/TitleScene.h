#pragma once
#include "Scene.h"
#include "TitleScreen.h"

/// <summary>
/// 
/// </summary>
class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Update() const override;

private:
	UniquePtr<TitleScreen> titleScreenUPtr;
};

