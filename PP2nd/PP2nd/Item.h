#pragma once
#include"define.h"

/// <summary>
/// ê›íuï®ÇÃäÓíÍÉNÉâÉX
/// </summary>

class Item
{
public:
	virtual void Init(int) = 0;
	virtual void Init(int,VECTOR) = 0;
	virtual ~Item() = default;
	virtual void OnEnter() const =0;
	virtual void OnExit() const =0;
	virtual void Draw() const = 0;
	virtual void Update() const = 0;
	virtual void Confirm() = 0;
	virtual int& GetMHandle() const = 0;

	Vector2Int GetScreenPos(VECTOR pos) const
	{
		Vector2Int result = Vector2Int();

		VECTOR buff = ConvWorldPosToScreenPos(pos);
		result.x = buff.x;
		result.y = buff.y;
		return result;
	};

	static int gHandleCheck;
	static int gHandleCross;
};


