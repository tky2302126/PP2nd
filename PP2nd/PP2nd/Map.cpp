#include "Map.h"
#include "Box.h"

Map::Map()
	:mapInfo(-1, -1, -1, -1),margin(0)
{
}

Map::~Map()
{
}

void Map::Init()
{
	margin = MAP_UNIT;
}

/// <summary>
/// マップの大きさに合わせて描画する
/// </summary>
/// <param name="mapInfo"></param>
void Map::Init(const _mapInfo& mapInfo)
{
	this->mapInfo = mapInfo;
	margin = MAP_UNIT;
	goalUPtr = make_unique<Box>();
	VECTOR pos = goalUPtr->GetBoxCenterPos(mapInfo.goalHeight, mapInfo.goalWidth,margin);
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
		for (int z = margin; z <= MAP_UNIT*10 - margin; z += MAP_UNIT)
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
		DrawLine3D(VGet(margin, 0, margin), VGet(mapInfo.width * MAP_UNIT+margin, 0, margin), outLineColor);
		DrawLine3D(VGet(margin, 0, mapInfo.height * MAP_UNIT+margin), VGet(mapInfo.width * MAP_UNIT+margin, 0, mapInfo.height * MAP_UNIT+margin), outLineColor);
		DrawLine3D(VGet(margin, 0, margin), VGet(margin, 0, mapInfo.height*MAP_UNIT+margin), outLineColor);
		DrawLine3D(VGet(mapInfo.width * MAP_UNIT+margin, 0, margin), VGet(mapInfo.width * MAP_UNIT+margin, 0, mapInfo.height*MAP_UNIT+margin), outLineColor);

		//z軸
		for(int x = 1; x<mapInfo.width;x++)
		{
			DrawLine3D(VGet(x * MAP_UNIT+margin, 0, margin), VGet(x * MAP_UNIT+margin, 0, mapInfo.height * MAP_UNIT + margin), ZAxizColor);
		}

		//x軸
		for(int z =1;z<mapInfo.height;z++)
		{
			DrawLine3D(VGet(margin, 0, z * MAP_UNIT + margin), VGet(mapInfo.width*MAP_UNIT+margin,0,z*MAP_UNIT+margin), XAxizcolor);
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
	VECTOR mouseWorldPos = ConvScreenPosToWorldPos(VGet(mouseInfo.position.x, mouseInfo.position.y, 0.0f));
	mouseWorldPos = Round(mouseWorldPos);
	VECTOR cameraDir = GameManager::GetInstance().GetCameraDirection();
	cameraDir = Round(cameraDir, 2);
	while(mouseWorldPos.y >=0)
	{
		mouseWorldPos = VAdd(mouseWorldPos, cameraDir);
	}
	return mouseWorldPos;
}
