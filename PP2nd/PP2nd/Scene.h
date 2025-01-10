#pragma once
#include "define.h"

/// <summary>
/// ゲームのシーン用の基底クラス
/// </summary>
class Scene
{
public:
	Scene();
	virtual  ~Scene() = default;
	virtual void Update() = 0;
	void SceneChange(SceneName name);
};

