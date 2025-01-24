#include "Map.h"
#include "Box.h"

Map::Map()
	:mapInfo(-1, -1, -1, -1)
{
}

Map::~Map()
{
}

void Map::Init()
{
	
}

/// <summary>
/// マップの大きさに合わせて描画する
/// </summary>
/// <param name="mapInfo"></param>
void Map::Init(const _mapInfo& mapInfo)
{
	this->mapInfo = mapInfo;
	goalUPtr = make_unique<Box>();
	VECTOR pos = goalUPtr->GetBoxCenterPos(mapInfo.goalHeight, mapInfo.goalWidth);
	goalUPtr->Init(pos, Tag::Goal);
}

void Map::UnInit()
{
}

void Map::Load(int day)
{
}
/// <summary>
/// ItemPanelから通知を受けるコールバック関数
/// </summary>
/// <param name="name"></param>
void Map::RegistHoldItem(ItemList name)
{
	int result = (int)name;
}

void Map::Draw()
{
	/// DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

#if _DEBUG
	int XAxizcolor = GetColor(255, 128, 255);
	int ZAxizColor = GetColor(128, 255, 255);
	/// デバッグ
	if(mapInfo.height == -1)
	{
		for (int z = 0; z <= MAP_UNIT*10 ; z += MAP_UNIT)
		{
			DrawLine3D(VGet(0, 0, z), VGet(MAP_UNIT*10, 0, z), XAxizcolor);
		}

		for (int x = 0; x <= MAP_UNIT*10; x += MAP_UNIT)
		{
			DrawLine3D(VGet(x, 0, 0), VGet(x, 0, MAP_UNIT*10), ZAxizColor);
		}
	}
	else
	{
		int outLineColor = GetColor(255, 255, 255);
		/// 外枠の描画
		DrawLine3D(VGet(0, 0, 0), VGet(mapInfo.width * MAP_UNIT+0, 0, 0), outLineColor);
		DrawLine3D(VGet(0, 0, mapInfo.height * MAP_UNIT), VGet(mapInfo.width * MAP_UNIT, 0, mapInfo.height * MAP_UNIT), outLineColor);
		DrawLine3D(VGet(0, 0, 0), VGet(0, 0, mapInfo.height*MAP_UNIT), outLineColor);
		DrawLine3D(VGet(mapInfo.width * MAP_UNIT, 0, 0), VGet(mapInfo.width * MAP_UNIT, 0, mapInfo.height*MAP_UNIT), outLineColor);

		//z軸
		for(int x = 1; x<mapInfo.width;x++)
		{
			DrawLine3D(VGet(x * MAP_UNIT, 0, 0), VGet(x * MAP_UNIT, 0, mapInfo.height * MAP_UNIT), ZAxizColor);
		}

		//x軸
		for(int z =1;z<mapInfo.height;z++)
		{
			DrawLine3D(VGet(0, 0, z * MAP_UNIT), VGet(mapInfo.width*MAP_UNIT,0,z*MAP_UNIT), XAxizcolor);
		}
	}
#endif

	
	/// ゴールポイントの描画
	if(mapInfo.goalHeight !=-1)
	{
		goalUPtr->Draw();
	}
	
	/// InputSystem監視
	VECTOR mouseWorldPos = GetMouseWorldPos();
	DrawFormatString(0, 90, GetColor(255, 255, 255), "mouseWorldPos(%f, %f, %f)", mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);

	///マウスの座標がグリッド内なら強調する
	/// グリッドの中央の一定範囲の矩形内なら、板ポリゴンを表示する

	float offset = 60.0f;



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
/// マウスのワールド座標取得
/// ワールド座標のyは0とする
///VECTOR ConvScreenPosToWorldPos_ZLinear()
/// マウスからレイを飛ばして0になるまで調べる

VECTOR Map::GetMouseWorldPos()
{
	MouseInfo mouseInfo = InputSystem::GetInstance().GetMouseInfo();
	VECTOR mouseWorldPos = ConvScreenPosToWorldPos(VGet(mouseInfo.position.x, mouseInfo.position.y, 0.5f));
	mouseWorldPos = Round(mouseWorldPos);
	VECTOR rayDir = VNorm(VSub(mouseWorldPos, GameManager::GetInstance().GetCameraPosition()));
	rayDir = Round(rayDir, 2);
	if (rayDir.y < 0) { rayDir = VScale(rayDir, -1.0); }
	while(mouseWorldPos.y >=0)
	{
		mouseWorldPos = VSub(mouseWorldPos, rayDir);
	}
	mouseWorldPos.y = 0;
	return mouseWorldPos;
}
