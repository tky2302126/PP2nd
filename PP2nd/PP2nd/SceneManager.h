#pragma once
#include "define.h"

class Scene;

/// <summary>
/// シーンの制御を行う
/// シングルトンで設計予定
/// ! managerクラスなのでインクルードはdefineのみ
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void UnInit();
	void Load(SceneName name);
	void LoadAsync(SceneName nextScene);
	void ChangeScene(SceneName name);
	void Update();
	static SceneManager& GetInstance();
	

private:
	static std::unique_ptr<SceneManager> Instance;
	Scene* scenePtr;
};

