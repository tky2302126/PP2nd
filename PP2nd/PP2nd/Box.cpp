#include "Box.h"

void Box::Init(const VECTOR& pos,const Tag& tag)
{
	this->pos = pos;
	this->tag = tag;
	// 頂点の計算
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

		vertex[0].pos = VGet(MinX,MinY,MinZ);
		vertex[0].norm = VGet(0,0,-1.0);
		vertex[0].spc = GetColorU8(0, 0, 0, 0);
		vertex[0].u = 0;
		vertex[0].v = 0;
		vertex[0].su = 0;
		vertex[0].sv = 0;

		vertex[1].pos = VGet(MaxX, MinY, MinZ);
		vertex[1].norm = VGet(0, 0, -1.0);
		vertex[1].spc = GetColorU8(0, 0, 0, 0);
		vertex[1].u = 0;
		vertex[1].v = 0;
		vertex[1].su = 0;
		vertex[1].sv = 0;

		vertex[2].pos = VGet(MaxX,MaxY,MinZ);
		vertex[2].norm = VGet(0,0,-1.0);
		vertex[2].spc = GetColorU8(0, 0, 0, 0);
		vertex[2].u = 0;
		vertex[2].v = 0;
		vertex[2].su = 0;
		vertex[2].sv = 0;

		vertex[3].pos = VGet(MinX,MaxY,MinZ);
		vertex[3].norm = VGet(0,0,-1.0);
		vertex[3].spc = GetColorU8(0, 0, 0, 0);
		vertex[3].u = 0;
		vertex[3].v = 0;
		vertex[3].su = 0;
		vertex[3].sv = 0;

		vertex[4].pos = VGet(MinX,MinY,MaxZ);
		vertex[4].norm = VGet(0,0,-1.0);
		vertex[4].spc = GetColorU8(0, 0, 0, 0);
		vertex[4].u = 0;
		vertex[4].v = 0;
		vertex[4].su = 0;
		vertex[4].sv = 0;

		vertex[5].pos = VGet(MaxX,MinY,MaxZ);
		vertex[5].norm = VGet(0,0,-1.0);
		vertex[5].spc = GetColorU8(0, 0, 0, 0);
		vertex[5].u = 0;
		vertex[5].v = 0;
		vertex[5].su = 0;
		vertex[5].sv = 0;

		vertex[6].pos = VGet(MaxX,MaxY,MaxZ);
		vertex[6].norm = VGet(0,0,-1.0);
		vertex[6].spc = GetColorU8(0, 0, 0, 0);
		vertex[6].u = 0;
		vertex[6].v = 0;
		vertex[6].su = 0;
		vertex[6].sv = 0;

		vertex[7].pos = VGet(MinX,MaxY,MaxZ);
		vertex[7].norm = VGet(0, 0, -1.0);
		vertex[7].spc = GetColorU8(0, 0, 0, 0);
		vertex[7].u = 0;
		vertex[7].v = 0;
		vertex[7].su = 0;
		vertex[7].sv = 0;
	}

	auto color = (tag == Tag::Start) ? COLOR_RED : COLOR_LIGHTBLUE;

	for(int i=0;i<8;i++)
	{
		vertex[i].dif = color;
	}

	//インデックスの初期化
	{
		// 前面
		index[0] = 0; index[1] = 2; index[2] = 1;
		index[3] = 0; index[4] = 3; index[5] = 2;

		//背面
		index[6] = 4; index[7] = 5; index[8] = 6;
		index[9] = 4; index[10] = 6; index[11] = 7;

		//左面
		index[12] = 0; index[13] = 7; index[14] = 3;
		index[15] = 0; index[16] = 4; index[17] = 7;

		//右面
		index[18] = 1; index[19] = 2; index[20] = 6;
		index[21] = 1; index[22] = 6; index[23] = 5;

		//上面
		index[24] = 2; index[25] = 3; index[26] = 7;
		index[27] = 2; index[28] = 7; index[29] = 6;

		//下面
		index[30] = 0; index[31] = 1; index[32] = 5;
		index[33] = 0; index[34] = 5; index[35] = 4;
	}
}

void Box::UnInit()
{
}

void Box::Draw()
{
	
	DrawPolygonIndexed3D(vertex, 8, index, 12, DX_NONE_GRAPH, false);

	{
		int white = GetColor(255, 255, 255);
		DrawLine3D(vertex[1].pos,vertex[2].pos,white);
		DrawLine3D(vertex[2].pos,vertex[3].pos,white);
		DrawLine3D(vertex[3].pos,vertex[0].pos,white);
								 		  
	    DrawLine3D(vertex[5].pos,vertex[6].pos,white);
	    DrawLine3D(vertex[6].pos,vertex[7].pos,white);
	    DrawLine3D(vertex[7].pos,vertex[4].pos,white);
								 		  
	    DrawLine3D(vertex[2].pos,vertex[6].pos,white);
	    DrawLine3D(vertex[3].pos,vertex[7].pos,white);
		
		/// 下部分4辺は描画しない
		// DrawLine3D(Vertex[0].pos,Vertex[1].pos,white);
	    // DrawLine3D(Vertex[1].pos,Vertex[5].pos,white);
	    // DrawLine3D(Vertex[0].pos,Vertex[4].pos,white);
	    // DrawLine3D(Vertex[4].pos,Vertex[5].pos,white);
	}
}
