#pragma once
#include "Enemy.h"

class Start;

class TestEnemy :public Enemy
{
public:
	TestEnemy();
	~TestEnemy();
	void Init(int) override;
	void Init(int,Start*) override;
	void Draw() const override;
	void Move() override;
	void Attack();
	void Update() override;
	void SetRoute(std::vector<Vector2Int> _route) override;
	void CompareRoute(std::vector<Vector2Int> _route) override;
	void RecalculateRoute() override;
	Start* GetMyStart() const override { return myStart; }
private:
	/// <summary>
	///  protetedで基底クラスで実装する
	/// </summary>
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

