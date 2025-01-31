#pragma once
#include "Enemy.h"
class TestEnemy :public Enemy
{
public:
	TestEnemy();
	~TestEnemy();
	void Init(int) override;
	void Draw() const override;
	void Move() const override;
	void Update() const override;
	void SetRoute(vector<Vector2Int> _route) override;
private:
	vector<Vector2Int> myRoute;
};

