#include "GameManager.h"

UniquePtr<GameManager> GameManager::Instance = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

/// <summary>
/// �X�v���C�g�f�[�^�ƃ��f���f�[�^�̓ǂݍ���
/// </summary>
void GameManager::Load()
{
#pragma region �f�o�b�O�p
	HandleData buff;
	string executablePath = GetExecutablePath();
	string GHandlePath = executablePath + "\\Resource\\cube.png";
	buff.GHandle = LoadGraph(GHandlePath.c_str());
	buff.MHandle = -1;
#pragma endregion

	for(int i=0;i<ItemList::ALL;i++)
	{
		
	}
}

void GameManager::Init()
{
	Load();
}

void GameManager::UnInit()
{
}

GameManager& GameManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = make_unique<GameManager>();
	}
	return *Instance;
}
