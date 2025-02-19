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
};

