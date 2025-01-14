#include "SceneManager.h"

unique_ptr<SceneManager> SceneManager::Instance = nullptr;

SceneManager::SceneManager()
{
	scenePtr = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	scenePtr = nullptr;
}

void SceneManager::UnInit()
{
}

void SceneManager::Load(SceneName name)
{
	if (scenePtr != nullptr) delete scenePtr;

	switch (name)
	{
	case Title:

		break;

	case Menu:

		break;

	case Option:

		break;

	case Main:

		break;

	case Test:
		scenePtr = new TestScene();
		break;

	default:
		break;
	}
}

/// <summary>
/// シーン遷移を実行する
/// ロードシーンをはさんでから遷移するため
/// preLoad -> name の順を想定
/// </summary>
/// <param name="name"></param>
void SceneManager::ChangeScene(SceneName name)
{
}

void SceneManager::Update()
{
	int startTime = GetNowCount();
	
	if (scenePtr != nullptr) { scenePtr->Update(); }

	int tookTime = GetNowCount() - startTime;
	int waitTime = FRAME_TIME_MS - tookTime;
	if (waitTime > 0) { Sleep(waitTime); }
}

SceneManager& SceneManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = make_unique<SceneManager>();
	}
	return *Instance;
}

