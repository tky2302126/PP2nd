#pragma once
#include "define.h"

/// <summary>
/// マップに描画する箱のクラス
/// </summary>
class Box
{
public:
	void Init();
	void Init(const VECTOR& pos,const Tag& tag);
	void UnInit();
	void Draw();
	VECTOR GetBoxCenterPos(int height, int width)
	{
		VECTOR pos;
		pos = VGet( width*MAP_UNIT-MAP_UNIT/2, MAP_UNIT/2, height*MAP_UNIT-MAP_UNIT/2);
		return pos;
	}
private:
	VERTEX3D Vertex[8];
	WORD Index[36];
	VECTOR pos;
	Tag tag;
	int lineColor;
};


