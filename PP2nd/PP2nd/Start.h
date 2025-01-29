#pragma once
#include"define.h"
class Start
{
public:
	void Init();
	void Init(Vector2Int pos);
	void UnInit();
	void SearchRoute();
	bool ReachGoal();
	Vector2Int& GetStartPos() { return pos; }
private:
	Vector2Int pos;
	vector<Vector2Int> route;
};

