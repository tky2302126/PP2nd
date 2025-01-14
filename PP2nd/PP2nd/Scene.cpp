#include "Scene.h"
#include "manager.h"

Scene::Scene()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
void Scene::SceneChange(SceneName name)
{
	SceneManager::GetInstance().ChangeScene(name);
}
