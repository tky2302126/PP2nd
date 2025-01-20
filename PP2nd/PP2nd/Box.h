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
	VECTOR GetBoxCenterPos(int height, int width, int margin)
	{
		VECTOR pos;
		pos = VGet( width*MAP_UNIT+margin/2, MAP_UNIT/2, height*MAP_UNIT+margin/2);
		return pos;
	}
private:
	VERTEX3D Vertex[8];
	WORD Index[36];
	VECTOR pos;
	Tag tag;
	int lineColor;
};


