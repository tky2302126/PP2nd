#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "TitleScene.h"
#include "Trial_Easy.h"

std::unique_ptr<SceneManager> SceneManager::Instance = nullptr;

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
	scenePtr->~Scene();
}

void SceneManager::Load(SceneName name)
{
	Scene* newScene = nullptr;
	
	switch (name)
	{
	case Title:
		newScene = new TitleScene();
		break;

	case Main:
		newScene = new Trial_Easy();
		break;

	case Test:
		newScene = new TestScene();
		break;

	default:
		return;
	}

	if (scenePtr != nullptr) delete scenePtr;
	scenePtr = newScene;
}

/// <summary>
/// シーン遷移を実行する
/// </summary>
/// <param name="name"></param>
void SceneManager::ChangeScene(SceneName name)
{
	Load(name);
}

void SceneManager::Update()
{
	/// ウィンドウアクティブを検知してカウントする
	int startTime = GetNowCount();


	/// マネージャークラスのアップデート
	Input().Update();
	EM().Update();

	if (scenePtr) { scenePtr->Update(); }

	int tookTime = GetNowCount() - startTime;
	int waitTime = FRAME_TIME_MS - tookTime;
	if (waitTime > 0) { std::this_thread::sleep_for(std::chrono::milliseconds(waitTime)); }
	TM().Update(FRAME_TIME_MS);
}

SceneManager& SceneManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = std::make_unique<SceneManager>();
	}
	return *Instance;
}

