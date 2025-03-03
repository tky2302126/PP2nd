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

	if(startPtrVec.empty())
	{
		Start* startPtr = new Start();
		Vector2Int startPos = { 0,9 };
		startPtr->Init(startPos);
		startPtrVec.push_back(startPtr);
	}
	Load(leela);
}

/// <summary>
/// 敵体力の補正値をセットする
/// </summary>
/// <param name="value"></param>
void EnemyManager::Setrevision(int value)
{
	revision = value;
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

void EnemyManager::SetStartPos(std::vector<Vector2Int> _startPos)
{
	if (!_startPos.empty())
	{
		for (int i = 0; i < _startPos.size(); i++)
		{
			Start* temp = new Start();
			Vector2Int startPos = { _startPos[i].x, _startPos[i].y };
			temp->Init(startPos);
			startPtrVec.push_back(temp);
		}
	}
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
void EnemyManager::SpawnEnemy(Vector2Int pos, EnemyList type)
{
	if (!startPtrVec.empty())
	{
		for (int i = 0; i < startPtrVec.size(); i++)
		{
			if(startPtrVec[i]->GetStartPos() == pos)
			{
				Enemy* enemyPtr = nullptr;
				switch (type)
				{
				case leela:
					enemyPtr = new Leela();
					enemyPtr->Init(mHandleResource[leela], startPtrVec[i]);
					break;
				case ALL:
					break;
				default:
					break;
				}
				if(enemyPtr != nullptr)
				{
					enemyPtr->SetRoute(startPtrVec[i]->GetRoute());
					enemyPtrVec.push_back(enemyPtr);
				}
			}
		}
	}
}

void EnemyManager::SpawnEnemyTest()
{
	if(!startPtrVec.empty())
	{
		for (int i = 0; i < startPtrVec.size(); i++)
		{
			Enemy* testEnemyPtr = new Leela();
			testEnemyPtr->Init(mHandleResource[leela], startPtrVec[i]);
			testEnemyPtr->SetRoute(startPtrVec[i]->GetRoute());
			enemyPtrVec.push_back(testEnemyPtr);
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
	for(int i=0; i< enemyPtrVec.size(); ++i)
	{
		if(enemyPtrVec[i] == enemy)
		{
			delete enemyPtrVec[i];
			enemyPtrVec.erase(enemyPtrVec.begin() + i);
			break;
		}
	}
}

bool EnemyManager::CanPlace(TerrainList name, Vector2Int pos)
{
	if (startPtrVec.empty()) return true;
	for(int i=0;i<startPtrVec.size();i++)
	{
		if(startPtrVec[i]->ReachGoal(name, pos) == false)
		{
			return false;
			break;
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
/// !mapかunmapの採用を検討
/// </summary>
/// <param name="name"></param>
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
