#pragma once
#include "Enemy.h"

class Start;

class TestEnemy :public Enemy
{
public:
	TestEnemy();
	~TestEnemy();
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
};

