#include "Map.h"
#include "Box.h"
#include "Cube.h"

Map::Map()
	:mapInfo(-1, -1, -1, -1)
{
}

Map::~Map()
{
	itemPtrVec.clear();
}

void Map::Init()
{
	MHandle = GameManager::GetInstance().GetHandleData(HDKey::Cube).MHandle;
}

/// <summary>
/// マップの大きさに合わせて描画する
/// </summary>
/// <param name="mapInfo"></param>
void Map::Init(const _mapInfo& mapInfo)
{
	this->mapInfo = mapInfo;
	/// !後で変える
	MHandle = GameManager::GetInstance().GetHandleData(HDKey::Cube).MHandle;
	goalUPtr = make_unique<Box>();
	VECTOR pos = goalUPtr->GetBoxCenterPos(mapInfo.goalHeight, mapInfo.goalWidth);
	goalUPtr->Init(pos, Tag::Goal);
	GameManager::GetInstance().InitTerrainInfo(mapInfo.width, mapInfo.height);
	/// terrainListからitemPtrVecをセットアップ

	/// EnemyManagerからスタート位置を受け取る
	vector<Vector2Int> startPos =  EnemyManager::GetInstance().GetStartPos();

	for(int i=0;i<startPos.size();i++)
	{
		AddStart(startPos[i]);
	}

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
void Map::RegistHoldItem(TerrainList name)
{
	holdItemTag = name;
	holdItem = true;
}

void Map::Draw()
{
	/// DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

#if _DEBUG
	/// マップのグリッド線を表示
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

	///スタートポイントの描画
	if(!startPtrVec.empty())
	{
		for(int i=0;i<startPtrVec.size();i++)
		{
			startPtrVec[i]->Draw();
		}
	}
	
	/// InputSystem監視
	VECTOR mouseWorldPos = GetMouseWorldPos();
	DrawFormatString(0, 90, GetColor(255, 255, 255), "mouseWorldPos(%.2f, %.2f, %.2f)", mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);

	///マウスの座標がグリッド内なら強調する
	/// グリッドの中央の一定範囲の矩形内なら、板ポリゴンを表示する

	float offset = 60.0f;
	MouseInfo currentInput = InputSystem::GetInstance().GetMouseInfo();
	
	/// canceled ->モデルの描画を終了
	if(currentInput.state.left == Canceled && holdItem)
	{
		holdItem = false;
		/// canceled && inGrid-> フィールド描画用のクラスを作成
		if(inGrid)
		{
			Item* itemPtr = nullptr;
			/// すでに配置済みならおけないようにする
			/// terrainInfoで調べる

			VECTOR pos = VGet(
				floor(mouseWorldPos.x / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2,
				0,
				floor(mouseWorldPos.z / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2
			);
			switch (holdItemTag)
			{
			
			
			case TerrainList::CUBE:
				itemPtr = new Cube();
				itemPtr->Init(MHandle,pos,this);
				break;

				/// アイテムを追加したら更新
			case TerrainList::ItemAll:
				break;
			
			default:
				break;
			}

			/// 配置確認を実行
			if(itemPtr != nullptr)
			{
				itemPtrVec.push_back(itemPtr);
				itemPtr->Confirm();
			}
		}
		else
		{
			TimeManager::GetInstance().ChangeGameSpeedSlower(false);
		}
		/// 後でアクティブに
	 	/// MHandle = -1;
	}

	/// 保持している場合
	if(holdItem)
	{
		/// マスに置こうとしているか調べる
		CHeckInGrid(mouseWorldPos);
		/// モデルの描画
		/// inGrid-> 座標を補正する
		VECTOR drawPos = mouseWorldPos;
		if(inGrid)
		{
			drawPos = VGet(
				floor(mouseWorldPos.x / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2,
				0,
				floor(mouseWorldPos.z / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2
			);
		}
		MV1SetScale(MHandle, VGet(1, 1, 1));
		MV1SetPosition(MHandle, drawPos);
		MV1DrawModel(MHandle);
	}

	if(!itemPtrVec.empty())
	{
		for(int i=0;i<itemPtrVec.size();i++)
		{
			itemPtrVec[i]->Update();
		}
	}


}
/// <summary>
/// カメラの移動に応じて描画範囲を変更できるようにする
/// </summary>
void Map::Update()
{
	Draw();
}

void Map::AddStart(Vector2Int pos)
{
	Box* startPtr = new Box();
	VECTOR VecPos = startPtr->GetBoxCenterPos(pos.y, pos.x);
	startPtr->Init(VecPos, Tag::Start);
	startPtrVec.push_back(startPtr); //! スマートポインタの場合は所有権を移動させる
}

void Map::AddGoal(Vector2Int pos)
{

}

void Map::RemoveItemPtr(Item* target)
{
	auto it = find(itemPtrVec.begin(), itemPtrVec.end(), target);
	if(it != itemPtrVec.end())
	{
		delete *it;
		itemPtrVec.erase(it);
	}
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

/// <summary>
/// マウスの座標がマスの中央付近に入っているか調べる
/// </summary>
void Map::CHeckInGrid(VECTOR& mousePos)
{
	if (mousePos.x < 0 || mousePos.z < 0 || mousePos.x > MAP_UNIT*mapInfo.width ||mousePos.z > mapInfo.height*MAP_UNIT) 
	{
		inGrid = false;
		return; 
	}
	
	float gridX = floor(mousePos.x / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2;
	float gridZ = floor(mousePos.z / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2;

	float threshold = MAP_UNIT / 5;

	/// 中央の座標からthreshold以内ならtrue
	if(abs(mousePos.x-gridX)<threshold && abs(mousePos.z -gridZ) < threshold)
	{
		inGrid = true;
	}
	else
	{
		false;
	}

}
