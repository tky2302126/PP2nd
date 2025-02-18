#pragma once
#include "Scene.h"

class TitleScreen;

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

