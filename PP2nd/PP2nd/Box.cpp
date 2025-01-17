#include "Box.h"

void Box::Init()
{
}

void Box::Init(const VECTOR& pos,const Tag& tag)
{
	this->pos = pos;
	this->tag = tag;
	// 頂点の計算
	if(tag == Tag::Goal || tag == Tag::Start)
	{
		float MinX;
		float MinY;
		float MinZ;
		float MaxX;
		float MaxY;
		float MaxZ;

		MinX = pos.x - MAP_UNIT / 2;
		MinY = pos.y - MAP_UNIT / 2;
		MinZ = pos.z - MAP_UNIT / 2;

		MaxX = pos.x + MAP_UNIT / 2;
		MaxY = pos.y + MAP_UNIT / 2;
		MaxZ = pos.z + MAP_UNIT / 2;

		Vertex[0].pos = VGet(MinX,MinY,MinZ);
		Vertex[0].norm = VGet(0,0,-1.0);
		Vertex[0].dif = GetColorU8(255, 0, 255, 0);
		Vertex[0].spc = GetColorU8(0, 0, 0, 0);
		Vertex[0].u = 0;
		Vertex[0].v = 0;
		Vertex[0].su = 0;
		Vertex[0].sv = 0;

		Vertex[1].pos = VGet(MaxX, MinY, MinZ);
		Vertex[1].norm = VGet(0, 0, -1.0);
		Vertex[1].dif = GetColorU8(255, 0, 255, 0);
		Vertex[1].spc = GetColorU8(0, 0, 0, 0);
		Vertex[1].u = 0;
		Vertex[1].v = 0;
		Vertex[1].su = 0;
		Vertex[1].sv = 0;

		Vertex[2].pos = VGet(MaxX,MaxY,MinZ);
		Vertex[2].norm = VGet(0,0,-1.0);
		Vertex[2].dif = GetColorU8(255, 0, 255, 0);
		Vertex[2].spc = GetColorU8(0, 0, 0, 0);
		Vertex[2].u = 0;
		Vertex[2].v = 0;
		Vertex[2].su = 0;
		Vertex[2].sv = 0;

		Vertex[3].pos = VGet(MinX,MaxY,MinZ);
		Vertex[3].norm = VGet(0,0,-1.0);
		Vertex[3].dif = GetColorU8(255, 0, 255, 0);
		Vertex[3].spc = GetColorU8(0, 0, 0, 0);
		Vertex[3].u = 0;
		Vertex[3].v = 0;
		Vertex[3].su = 0;
		Vertex[3].sv = 0;

		Vertex[4].pos = VGet(MinX,MinY,MaxZ);
		Vertex[4].norm = VGet(0,0,-1.0);
		Vertex[4].dif = GetColorU8(255, 0, 255, 0);
		Vertex[4].spc = GetColorU8(0, 0, 0, 0);
		Vertex[4].u = 0;
		Vertex[4].v = 0;
		Vertex[4].su = 0;
		Vertex[4].sv = 0;

		Vertex[5].pos = VGet(MaxX,MinY,MaxZ);
		Vertex[5].norm = VGet(0,0,-1.0);
		Vertex[5].dif = GetColorU8(255, 0, 255, 0);
		Vertex[5].spc = GetColorU8(0, 0, 0, 0);
		Vertex[5].u = 0;
		Vertex[5].v = 0;
		Vertex[5].su = 0;
		Vertex[5].sv = 0;

		Vertex[6].pos = VGet(MaxX,MaxY,MaxZ);
		Vertex[6].norm = VGet(0,0,-1.0);
		Vertex[6].dif = GetColorU8(255,0, 255, 0);
		Vertex[6].spc = GetColorU8(0, 0, 0, 0);
		Vertex[6].u = 0;
		Vertex[6].v = 0;
		Vertex[6].su = 0;
		Vertex[6].sv = 0;

		Vertex[7].pos = VGet(MinX,MaxY,MaxZ);
		Vertex[7].norm = VGet(0, 0, -1.0);
		Vertex[7].dif = GetColorU8(255, 0, 255, 0);
		Vertex[7].spc = GetColorU8(0, 0, 0, 0);
		Vertex[7].u = 0;
		Vertex[7].v = 0;
		Vertex[7].su = 0;
		Vertex[7].sv = 0;
	}

	//インデックスの初期化
	{

		//{
		//	// 前面
		//	0, 2, 1, // 三角形 1
		//		0, 3, 2, // 三角形 2

		//		// 背面
		//		4, 5, 6, // 三角形 3
		//		4, 6, 7, // 三角形 4

		//		// 左面
		//		0, 7, 3, // 三角形 5
		//		0, 4, 7, // 三角形 6

		//		// 右面
		//		1, 2, 6, // 三角形 7
		//		1, 6, 5, // 三角形 8

		//		// 上面
		//		2, 3, 7, // 三角形 9
		//		2, 7, 6, // 三角形 10

		//		// 下面
		//		0, 1, 5, // 三角形 11
		//		0, 5, 4  // 三角形 12
		//};

		// 前面
		Index[0] = 0; Index[1] = 2; Index[2] = 1;
		Index[3] = 0; Index[4] = 3; Index[5] = 2;

		//背面
		Index[6] = 4; Index[7] = 5; Index[8] = 6;
		Index[9] = 4; Index[10] = 6; Index[11] = 7;

		//左面
		Index[12] = 0; Index[13] = 7; Index[14] = 3;
		Index[15] = 0; Index[16] = 4; Index[17] = 7;

		//右面
		Index[18] = 1; Index[19] = 2; Index[20] = 6;
		Index[21] = 1; Index[22] = 6; Index[23] = 5;

		//上面
		Index[24] = 2; Index[25] = 3; Index[26] = 7;
		Index[27] = 2; Index[28] = 7; Index[29] = 6;

		//下面
		Index[30] = 0; Index[31] = 1; Index[32] = 5;
		Index[33] = 0; Index[34] = 5; Index[35] = 4;
	}
}

void Box::UnInit()
{
}

void Box::Draw()
{
	
	DrawPolygonIndexed3D(Vertex, 8, Index, 12, DX_NONE_GRAPH, false);

	if(tag == Tag::Goal)
	{
		int white = GetColor(255, 255, 255);
		DrawLine3D(Vertex[0].pos,Vertex[1].pos,white);
		DrawLine3D(Vertex[1].pos,Vertex[2].pos,white);
		DrawLine3D(Vertex[2].pos,Vertex[3].pos,white);
		DrawLine3D(Vertex[3].pos,Vertex[0].pos,white);
								 		  
	    DrawLine3D(Vertex[4].pos,Vertex[5].pos,white);
	    DrawLine3D(Vertex[5].pos,Vertex[6].pos,white);
	    DrawLine3D(Vertex[6].pos,Vertex[7].pos,white);
	    DrawLine3D(Vertex[7].pos,Vertex[4].pos,white);
								 		  
	    DrawLine3D(Vertex[0].pos,Vertex[4].pos,white);
	    DrawLine3D(Vertex[1].pos,Vertex[5].pos,white);
	    DrawLine3D(Vertex[2].pos,Vertex[6].pos,white);
	    DrawLine3D(Vertex[3].pos,Vertex[7].pos,white);
	}
}
