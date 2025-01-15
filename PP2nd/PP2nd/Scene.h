#pragma once
#include "define.h"
#include "manager.h"

/// <summary>
/// �Q�[���̃V�[���p�̊��N���X
/// </summary>
class Scene
{
public:
	Scene() {};
	virtual  ~Scene() = default;
	virtual void Update() = 0;
	
	/// <summary>
	/// �V�[���J�ڂ����s
	/// </summary>
	/// <param name="name">�J�ڐ�̃V�[����</param>
	void SceneChange(SceneName name)
	{
		SceneManager::GetInstance().ChangeScene(name);
	}

};

