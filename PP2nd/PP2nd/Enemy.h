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
	virtual void Init(int) = 0;
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
	std::vector<Vector2Int> myRoute;   /// 
	std::vector<Vector2Int> tempRoute; /// 一時的な経路
	Start* myStart;
	Vector2Int oldPos = { -1,-1 };
	bool pathFound = true; /// ルート探索済みであることを示す
	bool move = true;
	bool attack = false;
	int health;
	int currentHealth;
	int InGaugeGH;
	int OutGaugeGH;
	int attackBeginTime = -1;
};

