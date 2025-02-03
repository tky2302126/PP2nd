#pragma once
#include "define.h"
#include "Enemy.h"
#include "Start.h"
/// <summary>
/// 敵の生成、ルート設定、ステージ全体の敵状況の管理
/// スタート地点からゴールに向かってルートを求める(マップに線を引く)
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
	void InitTest();
	void LoadTest();
	vector<Vector2Int> GetStartPos();
	void DrawRouteTest();
	void ReCalculateRoute();
	void SpawnEnemyTest();
	void IncreaseTrialCount();
	void ResetTrialCount();
	int GetTrialCount() { return trialCount; }
private:
	
	/// ゴールまでのルート
	/// スタートとゴール、それまでに経由する点を保有
	vector<Start*> startPtrVec;

	/// <summary>
	/// ゴールに向かう敵
	/// </summary>
	vector<Enemy*> enemyPtrVec;
	int trialCount = 0; // 経路探索の試行回数
	static UniquePtr<EnemyManager> Instance;
};

