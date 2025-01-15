#pragma once
#include "define.h"
#include "manager.h"

/// <summary>
/// ゲームのシーン用の基底クラス
/// </summary>
class Scene
{
public:
	Scene() {};
	virtual  ~Scene() = default;
	virtual void Update() = 0;
	
	/// <summary>
	/// シーン遷移を実行
	/// </summary>
	/// <param name="name">遷移先のシーン名</param>
	void SceneChange(SceneName name)
	{
		SceneManager::GetInstance().ChangeScene(name);
	}

};

