#pragma once
#include "define.h"

/// <summary>
/// �Q�[���̃V�[���p�̊��N���X
/// </summary>
class Scene
{
public:
	Scene();
	virtual  ~Scene() = default;
	virtual void Update() = 0;
	void SceneChange(SceneName name);
};

