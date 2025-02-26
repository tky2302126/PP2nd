#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "TitleScene.h"

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
}

void SceneManager::Load(SceneName name)
{
	if (scenePtr != nullptr) delete scenePtr;

	switch (name)
	{
	case Title:
		scenePtr = new TitleScene();
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

void SceneManager::LoadAsync(SceneName nextScene)
{

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
	/// ウィンドウアクティブを検知してカウントする
	int startTime = GetNowCount();


	/// マネージャークラスのアップデート
	Input().Update();
	EnemyManager::GetInstance().Update();

	if (scenePtr != nullptr) { scenePtr->Update(); }

	int tookTime = GetNowCount() - startTime;
	int waitTime = FRAME_TIME_MS - tookTime;
	if (waitTime > 0) { Sleep(waitTime); }
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

