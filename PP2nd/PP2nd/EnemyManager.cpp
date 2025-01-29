#include "EnemyManager.h"

UniquePtr<EnemyManager> EnemyManager::Instance = nullptr;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

EnemyManager& EnemyManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = make_unique<EnemyManager>();
	}
	return *Instance;
}

void EnemyManager::Init()
{
}

void EnemyManager::UnInit()
{
}

void EnemyManager::InitStart()
{
}
