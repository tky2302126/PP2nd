#pragma once
#include"define.h"
class Start
{
public:
	void Init();
	void Init(Vector2Int pos);
	void UnInit();
	void SearchRoute();
	bool ReachGoal(TerrainList name, Vector2Int pos);
	Vector2Int& GetStartPos() { return pos; }
	std::vector<Vector2Int> GetRoute() const { return route; }
	void DrawRouteTest();
	int BaseHealth() const { return baseHealth; }
private:
	Vector2Int pos;
	std::vector<Vector2Int> route;
	int baseHealth;
};

