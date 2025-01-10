#pragma once
#include "define.h"
#include "Scene.h"
#include "TestScene.h"

/// <summary>
/// シーンの制御を行う
/// シングルトンで設計予定
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
	static SceneManager* GetInstance();
	

private:
	static SceneManager* Instance;
	Scene* scenePtr;

	static void CreateInstance();
};

