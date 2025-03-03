#pragma once
#include "define.h"

/// <summary>
/// マップに描画する箱のクラス
/// </summary>
class Box
{
public:
	void Init(const VECTOR& pos,const Tag& tag);
	void UnInit();
	void Draw();
	/// <summary>
	/// ワールド座標で中心を求める
	/// </summary>
	/// <param name="height">配列座標 y</param>
	/// <param name="width">配列座標 x</param>
	/// <returns>ワールド座標</returns>
	VECTOR GetBoxCenterPos(int height, int width)
	{
		VECTOR pos;
		pos = VGet( width*MAP_UNIT+MAP_UNIT/2, MAP_UNIT/2, height*MAP_UNIT+MAP_UNIT/2);
		return pos;
	}
private:
	VERTEX3D vertex[8];
	WORD index[36];
	VECTOR pos;
	Tag tag;
};


