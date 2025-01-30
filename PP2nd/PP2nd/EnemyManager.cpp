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
	Vector2Int startPos = { 13,5 };
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
