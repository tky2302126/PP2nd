#pragma once
#include"define.h"

/// <summary>
/// 設置物の基底クラス
/// </summary>

class Map;

class Item
{
public:
	virtual void Init(int,VECTOR,Map*) = 0;
	virtual ~Item() = default;
	virtual void Draw() const = 0;
	virtual void Update() = 0;
	virtual void Confirm() = 0;
	virtual int& GetMHandle() const = 0;
	virtual VECTOR GetPosition() const = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	/// <returns>破壊されるかどうか trueなら破壊</returns>
	virtual bool TakeDamege(int damage) =0;
	static int gHandleCheck;
	static int gHandleCross;
};


