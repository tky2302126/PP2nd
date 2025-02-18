#pragma once
#include "Scene.h"
#include "TitleScreen.h"

/// <summary>
/// 
/// </summary>
class Title :public Scene
{
public:
	Title();
	~Title();

	void Update() const override;

private:
	UniquePtr<TitleScreen> titleScreenUPtr;
};

