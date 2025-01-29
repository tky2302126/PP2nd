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
private:
	
	/// ゴールまでのルート
	/// スタートとゴール、それまでに経由する点を保有
	vector<Start*> startPtrVec;

	static UniquePtr<EnemyManager> Instance;
};

