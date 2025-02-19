#pragma once
#include "define.h"
#include "Enemy.h"
#include "Start.h"
/// <summary>
/// 敵の生成、ルート設定、ステージ全体の敵状況の管理
/// スタート地点からゴールに向かってルートを求める(マップに線を引く)
/// !todo Speedの概念
/// </summary>
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	static EnemyManager& GetInstance();
	void Init();
	void UnInit();
	void InitStart();
	void Load(int day);
	void Update();
	std::vector<Vector2Int> GetStartPos();
	void DrawRouteTest();
	void ReCalculateRoute();
	void IncreaseTrialCount();
	void ResetTrialCount();
	int  GetTrialCount() { return trialCount; }
	void RemoveEnemy(Enemy* enemy);
	bool CanPlace(TerrainList name, Vector2Int pos);
	void SpawnEnemyTest();
	void InitTest();
	void LoadTest();
private:
	
	/// ゴールまでのルート
	/// スタートとゴール、それまでに経由する点を保有
	std::vector<Start*> startPtrVec;

	/// <summary>
	/// ゴールに向かう敵
	/// </summary>
	std::vector<Enemy*> enemyPtrVec;
	int trialCount = 0; // 経路探索の試行回数
	static UniquePtr<EnemyManager> Instance;

	int enemyCountTest = 0;
};

