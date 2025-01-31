#pragma once
#include "define.h"

/// <summary>
/// エネミーの基底クラス
/// </summary>
class Enemy
{
public:
	virtual ~Enemy() = default;
	virtual void Init(int) = 0;
	virtual void Draw() const = 0;
	virtual void Move() const = 0;
	virtual void Update() const = 0;
	virtual void SetRoute(vector<Vector2Int>) = 0;
};

