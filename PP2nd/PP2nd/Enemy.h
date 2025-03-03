#pragma once
#include "define.h"

class Start;

/// <summary>
/// エネミーの基底クラス
/// </summary>
class Enemy
{
public:
	virtual ~Enemy() = default;
	virtual void Init(int, Start*) = 0;
	virtual void Draw() const = 0;
	virtual void Move() = 0;
	virtual void Update() = 0;
	virtual void SetRoute(std::vector<Vector2Int>) = 0;
	virtual void CompareRoute(std::vector<Vector2Int>) = 0;
	virtual void RecalculateRoute() = 0;
	virtual Start* GetMyStart() const =0;
protected:
	VECTOR position;
	std::vector<Vector2Int> myRoute;   /// 自身の進行ルート
	std::vector<Vector2Int> tempRoute; /// 再計算に避難する用の一時的な経路
	Start* myStart; // スポーン地点 ルート再計算の際に使用
	Vector2Int oldPos = { -1,-1 };
	bool pathFound = true; /// ルート探索済みであることを示す
	bool move = true;
	bool attack = false;
	int maxHealth;         /// HPの最大値
	int currentHealth;     /// HPの現在の値
	int InGaugeGH;         /// 自身のHPを表示するUI(内枠)
	int OutGaugeGH;		   /// 自身のHPを表示するUI(外枠)
	int attackBeginTime = -1;
};

