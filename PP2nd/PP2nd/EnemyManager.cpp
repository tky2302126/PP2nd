#include "EnemyManager.h"
#include "TestEnemy.h"

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
	Vector2Int startPos = { 11,4 };
	startPtr->Init(startPos);
	startPtrVec.push_back(startPtr);
}

/// <summary>
/// マップに描画するスタート位置を取得する
/// </summary>
/// <returns></returns>
vector<Vector2Int> EnemyManager::GetStartPos()
{
	vector<Vector2Int> startPosVec = vector<Vector2Int>();
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
			//	if (enemyCountTest > 1) { continue; }
			Enemy* testEnemyPtr = new TestEnemy();
			testEnemyPtr->Init(-1,startPtrVec[i]);
			testEnemyPtr->SetRoute(startPtrVec[i]->GetRoute());
			enemyPtrVec.push_back(testEnemyPtr);
			enemyCountTest++;
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
void EnemyManager::Load(int day)
{

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
