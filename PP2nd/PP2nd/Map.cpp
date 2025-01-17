#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init()
{
	margin = MAP_HEIGHT * MAP_MARGIN;
}

void Map::UnInit()
{
}

void Map::Load(int day)
{
}

void Map::Draw()
{
	/// DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

#if _DEBUG
	int XAxizcolor = GetColor(255, 128, 255);
	int ZAxizColor = GetColor(128, 255, 255);

	for (int z = margin; z <= MAP_HEIGHT - margin; z += MAP_UNIT)
	{
		DrawLine3D(VGet(0, 0, z), VGet(MAP_WIDTH, 0, z), XAxizcolor);
	}

	for (int x = 0; x <= MAP_WIDTH; x += MAP_UNIT)
	{
		DrawLine3D(VGet(x, 0, 0), VGet(x, 0, MAP_HEIGHT), ZAxizColor);
	}

	/// ゴールポイントの描画

#endif

	


	// 原点に球を描画
	//DrawSphere3D(VGet(0, 0, 0), 50, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}
/// <summary>
/// カメラの移動に応じて描画範囲を変更できるようにする
/// </summary>
void Map::Update()
{
	Draw();
}

void Map::LoadTerrainInfo(int)
{
}

void Map::LoadMapInfo(int)
{
}
