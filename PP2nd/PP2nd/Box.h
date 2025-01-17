#pragma once
#include "define.h"

/// <summary>
/// マップに描画するアイテムのクラス
/// </summary>
class Box
{
public:
	void Init();
	void Init(const VECTOR& pos,const Tag& tag);
	void UnInit();
	void Draw();
private:
	VERTEX3D Vertex[8];
	WORD Index[36];
	VECTOR pos;
	Tag tag;
	int lineColor;
};

