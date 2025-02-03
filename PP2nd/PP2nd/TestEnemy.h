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
	void Update() override;
	void SetRoute(vector<Vector2Int> _route) override;
	void CompareRoute(vector<Vector2Int> _route) override;
	void RecalculateRoute() override;
	Start* GetMyStart() const override { return myStart; }
private:
	VECTOR position;
	vector<Vector2Int> myRoute;
	vector<Vector2Int> tempRoute; /// 一時的な経路
	Start* myStart;
	bool pathFound = true; /// ルート探索済みであることを示す
};

