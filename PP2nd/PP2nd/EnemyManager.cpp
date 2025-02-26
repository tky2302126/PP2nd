#include "EnemyManager.h"
#include "Enemies.h"
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
		Instance = std::make_unique<EnemyManager>();
	}
	return *Instance;
}

void EnemyManager::Init()
{
}

/// <summary>
/// デバッグ用のイニシャライズ
/// </summary>
void EnemyManager::InitTest()
{

}
/// <summary>
/// デバッグ用のロード
/// </summary>
void EnemyManager::LoadTest()
{
	Start* startPtr = new Start();
	Vector2Int startPos = { 20,4 };
	startPtr->Init(startPos);
	startPtrVec.push_back(startPtr);
	Load(leela);
}

/// <summary>
/// マップに描画するスタート位置を取得する
/// </summary>
/// <returns></returns>
std::vector<Vector2Int> EnemyManager::GetStartPos()
{
	std::vector<Vector2Int> startPosVec = std::vector<Vector2Int>();
	if(!startPtrVec.empty())
	{
		for(int i=0;i<startPtrVec.size();i++)
		{
			startPosVec.push_back(startPtrVec[i]->GetStartPos());
		}
	}
	return startPosVec;
}

void EnemyManager::DrawRouteTest()
{
	if (!startPtrVec.empty())
	{
		for (int i = 0; i < startPtrVec.size(); i++)
		{
			startPtrVec[i]->DrawRouteTest();
		}
	}
}

void EnemyManager::ReCalculateRoute()
{
	if(!startPtrVec.empty())
	{
		for(int i=0;i<startPtrVec.size();i++)
		{
			startPtrVec[i]->SearchRoute();
		}
	}

	if(!enemyPtrVec.empty())
	{
		for(int i=0; i<enemyPtrVec.size();i++)
		{
			enemyPtrVec[i]->CompareRoute(enemyPtrVec[i]->GetMyStart()->GetRoute());
		}
	}
}

void EnemyManager::SpawnEnemyTest()
{
	if(!startPtrVec.empty())
	{
		for (int i = 0; i < startPtrVec.size(); i++)
		{
			// if (enemyCountTest > 0) { continue; }
			Enemy* testEnemyPtr = new Leela();
			testEnemyPtr->Init(mHandleResource[leela], startPtrVec[i]);
			testEnemyPtr->SetRoute(startPtrVec[i]->GetRoute());
			enemyPtrVec.push_back(testEnemyPtr);
			// enemyCountTest++;
		}
	}
}

void EnemyManager::IncreaseTrialCount()
{
	trialCount++;
}

void EnemyManager::ResetTrialCount()
{
	trialCount = 0;
}

void EnemyManager::RemoveEnemy(Enemy* enemy)
{
	int index = 0;
	while (true)
	{
		if(enemyPtrVec[index] == enemy)
		{
			delete enemyPtrVec[index];
			enemyPtrVec.erase(enemyPtrVec.begin() + index);
			break;
		}
		index++;
	}
}

bool EnemyManager::CanPlace(TerrainList name, Vector2Int pos)
{
	if(startPtrVec.size()>=1)
	{
		for(int i=0;i<startPtrVec.size();i++)
		{
			if(startPtrVec[i]->ReachGoal(name, pos) == false)
			{
				return false;
				break;
			}
		}
	}
	return true;
}

void EnemyManager::UnInit()
{
}

void EnemyManager::InitStart()
{
}

/// <summary>
/// csvなどから地形情報を読み取る
/// </summary>
/// <param name="day"></param>
void EnemyManager::Load(EnemyList name)
{
	switch (name)
	{
	case leela:
		mHandleResource[leela] = MV1LoadModel("./Resource/Leela.mv1");
		break;
	case ALL:
		break;
	default:
		break;
	}
}

void EnemyManager::Update()
{
	if(!enemyPtrVec.empty())
	{
		for(int i=0; i<enemyPtrVec.size();i++)
		{
			enemyPtrVec[i]->Update();
		}
	}
}
