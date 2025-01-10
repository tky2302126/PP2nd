#include "SceneManager.h"

SceneManager* SceneManager::Instance = nullptr;

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
/// �V�[���J�ڂ����s����
/// ���[�h�V�[�����͂���ł���J�ڂ��邽��
/// preLoad -> name �̏���z��
/// </summary>
/// <param name="name"></param>
void SceneManager::ChangeScene(SceneName name)
{
}

void SceneManager::Update()
{
	if (scenePtr != nullptr) { scenePtr->Update(); }
}

SceneManager* SceneManager::GetInstance()
{
	if(Instance == nullptr)
	{
		CreateInstance();
	}
	return Instance;
}

void SceneManager::CreateInstance()
{
	Instance = new SceneManager();
}
