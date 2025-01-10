#pragma once
#include "define.h"
#include "Scene.h"
#include "TestScene.h"

/// <summary>
/// �V�[���̐�����s��
/// �V���O���g���Ő݌v�\��
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void UnInit();
	void Load(SceneName name);
	void ChangeScene(SceneName name);
	void Update();
	static SceneManager& GetInstance();
	

private:
	static unique_ptr<SceneManager> Instance;
	Scene* scenePtr;

};

