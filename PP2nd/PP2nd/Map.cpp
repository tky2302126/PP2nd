#include "Map.h"
#include "Box.h"
#include "Cube.h"
#include "Items.h"

Map::Map()
	:mapInfo(-1, -1, -1, -1)
{
}

Map::~Map()
{
	itemPtrVec.clear();
}

/// <summary>
/// タイトルシーン用のイニシャライズ
/// </summary>
void Map::Init()
{
	MHandle = GameM().GetHandleData(HDKey::Cube).MHandle;
	mapInfo = {25, 25, -1, -1};
	mapTexture = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_BaseColor.png");

	/// シェーダーの準備 vsoとpsoファイルの準備が必要？要調査
	//baseTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_BaseColor.png");
	//normalTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_Normal.png");
	//aoTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_AO.png");
	//roughnessTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_Roughness.png");
}

/// <summary>
/// マップの大きさに合わせて描画する
/// </summary>
/// <param name="mapInfo"></param>
void Map::Init(const _mapInfo& mapInfo)
{
	this->mapInfo = mapInfo;
	goalUPtr = std::make_unique<Box>();
	VECTOR pos = goalUPtr->GetBoxCenterPos(mapInfo.goalHeight, mapInfo.goalWidth);
	goalUPtr->Init(pos, Tag::Goal);
	/// terrainListからitemPtrVecをセットアップ
	auto terrainInfo = GameM().GetTerrainInfo();
	if(!terrainInfo.empty())
	{
		for(int y=0;y<terrainInfo.size();y++)
		{
			for(int x=0;x<terrainInfo[y].size();x++)
			{

				if(terrainInfo[y][x] == TerrainList::CUBE)
				{
					Item* itemPtr = new Cube();
					MHandle = GameM().GetHandleData(HDKey::Cube).MHandle;
					VECTOR pos = VGet(
						x * MAP_UNIT + MAP_UNIT / 2,
						0,
						y * MAP_UNIT + MAP_UNIT / 2
					);
					itemPtr->Init(MHandle, pos,this);
					itemPtrVec.push_back(itemPtr);
					MHandle = -1;
				}

				if (terrainInfo[y][x] == TerrainList::DECOY)
				{
					Item* itemPtr = new Decoy();
					MHandle = GameM().GetHandleData(HDKey::Cube).MHandle;
					VECTOR pos = VGet(
						x * MAP_UNIT + MAP_UNIT / 2,
						0,
						y * MAP_UNIT + MAP_UNIT / 2
					);
					itemPtr->Init(MHandle, pos, this);
					itemPtrVec.push_back(itemPtr);
					MHandle = -1;
				}
			}
		}
	}

	/// EnemyManagerからスタート位置を受け取る
	std::vector<Vector2Int> startPos = EnemyM().GetStartPos();

	for(int i=0;i<startPos.size();i++)
	{
		AddStart(startPos[i]);
	}

	//mapTexture = LoadGraph("./Resource/MapSample.jpeg");
	mapTexture = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_BaseColor.png");

	/// シェーダーの準備 vsoとpsoファイルの準備が必要？要調査
	//baseTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_BaseColor.png");
	//normalTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_Normal.png");
	//aoTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_AO.png");
	//roughnessTex = LoadGraph("./Resource/SandyGravel01_MR_2K/SandyGravel01_2K_Roughness.png");
}

void Map::UnInit()
{
	for(int i=0;i<startPtrVec.size();i++)
	{
		delete startPtrVec[i];
	}

	startPtrVec.clear();

	for(int i=0;i<itemPtrVec.size();i++)
	{
		delete itemPtrVec[i];
	}

	itemPtrVec.clear();

	DeleteGraph(mapTexture);

	DeleteGraph(baseTex);
	DeleteGraph(normalTex);
	DeleteGraph(aoTex);
	DeleteGraph(roughnessTex);
}

void Map::Load(int day)
{
}

/// <summary>
/// 地形情報が変更されたとき反映する
/// </summary>
void Map::Reload()
{
	auto terrainInfo = CGameM().GetTerrainInfo();

	/// ダメージ処理
	auto damageInfo = GameM().GetDamegeInfo();
	
	for (auto it = itemPtrVec.begin(); it != itemPtrVec.end();) 
	{
		auto itemPos = (*it)->GetPosition();
		for(auto& [pos, damage]: damageInfo)
		{
			if(itemPos.x == pos.x && itemPos.z == pos.z)
			{
				if((*it)->TakeDamege(damage))
				{
					it = itemPtrVec.erase(it);
				}
				else
				{
					it++;
				}
			}
			break;
		}
	}
	damageInfo.clear();
	GameM().CheckedTerrainInfo();

}
/// <summary>
/// ItemPanelから通知を受けるコールバック関数
/// </summary>
/// <param name="name"></param>
void Map::RegistHoldItem(TerrainList name)
{
	holdItemTag = name;
	holdItem = true;
	switch (name)
	{
	case TerrainList::CUBE:
		MHandle = GameM().GetHandleData(HDKey::Cube).MHandle;
		break;
	case TerrainList::DECOY:
		MHandle = GameM().GetHandleData(HDKey::Decoy).MHandle;
		break;
	case TerrainList::SWAMP:
		MHandle = GameM().GetHandleData(HDKey::Swamp).MHandle;
		break;
	}
}

/// <summary>
/// todo : マップの描画
/// 板ポリゴンにスプライトを貼る形で実装する
/// </summary>
void Map::Draw()
{
#if _DEBUG
	// DrawDebugGrid();
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
	// DrawFormatString(0, 90, GetColor(255, 255, 255), "mouseWorldPos(%.2f, %.2f, %.2f)", mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);

	///マウスの座標がグリッド内なら強調する
	/// グリッドの中央の一定範囲の矩形内なら、板ポリゴンを表示する

	float offset = 60.0f;
	MouseInfo currentInput = Input().GetMouseInfo();
	
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
			Vector2Int terrainPos = { floor(mouseWorldPos.x / MAP_UNIT), floor(mouseWorldPos.z / MAP_UNIT) };
			auto terrainInfo = CGameM().GetTerrainInfo();
			if (terrainInfo[terrainPos.y][terrainPos.x] != TerrainList::None) return;


			VECTOR pos = VGet(
				floor(mouseWorldPos.x / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2,
				0,
				floor(mouseWorldPos.z / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2
			);
			switch (holdItemTag)
			{
			
			
			case TerrainList::CUBE:
				/// 配置した時にルートが消えないか調査
				if (!EnemyM().CanPlace(TerrainList::CUBE, terrainPos))
				{
					/// 配置不可なダイアログを表示

					break;
				}
				itemPtr = new Cube();
				itemPtr->Init(MHandle,pos,this);
				break;

				/// アイテムを追加したら更新

			case TerrainList::DECOY:
				if (!EnemyM().CanPlace(TerrainList::DECOY, terrainPos))
				{
					/// 配置不可なダイアログを表示

					break;
				}
				itemPtr = new Decoy();
				itemPtr->Init(MHandle, pos, this);
				break;
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
			TimeM().ChangeGameSpeedSlower(false);
		}
		/// 後でアクティブに
	 	MHandle = -1;
	}

	/// 保持している場合
	if(holdItem)
	{
		DrawDebugGrid();
		/// マスに置こうとしているか調べる
		CheckInGrid(mouseWorldPos);
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

	DrawPolygonIndexed3D(vertices, 4, index, 2, mapTexture, TRUE);
	DrawPolygonIndexed3D(vertices2, 4, index, 2, mapTexture, TRUE);
	DrawPolygonIndexed3D(vertices3, 4, index, 2, mapTexture, TRUE);
	DrawPolygonIndexed3D(vertices4, 4, index, 2, mapTexture, TRUE);
}

/// <summary>
/// タイトルシーン用の描画
/// </summary>
/// <param name=""></param>
void Map::Draw(SceneName& name)
{
	if (name == Option) { return; }

	/// InputSystem監視
	VECTOR mouseWorldPos = GetMouseWorldPos();
	// DrawFormatString(0, 90, GetColor(255, 255, 255), "mouseWorldPos(%.2f, %.2f, %.2f)", mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);

	///マウスの座標がグリッド内なら強調する
	/// グリッドの中央の一定範囲の矩形内なら、板ポリゴンを表示する

	float offset = 60.0f;
	MouseInfo currentInput = Input().GetMouseInfo();

	/// canceled ->モデルの描画を終了
	if (currentInput.state.left == Canceled && holdItem)
	{
		holdItem = false;
		/// canceled && inGrid-> フィールド描画用のクラスを作成
		if (inGrid)
		{
			Item* itemPtr = nullptr;
			VECTOR pos = VGet(
				floor(mouseWorldPos.x / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2,
				0,
				floor(mouseWorldPos.z / MAP_UNIT) * MAP_UNIT + MAP_UNIT / 2
			);
			switch (holdItemTag)
			{


			case TerrainList::CUBE:
				/// 配置した時にルートが消えないか調査
				itemPtr = new Cube();
				itemPtr->Init(MHandle, pos, this);
				break;
				AudioM().PlaySE(LOWBON);

				/// アイテムを追加したら更新

			case TerrainList::DECOY:
				itemPtr = new Decoy();
				itemPtr->Init(MHandle, pos, this);
				break;
			case TerrainList::ItemAll:
				break;

			default:
				break;
			}

			/// 配置確認を実行
			if (itemPtr != nullptr)
			{
				itemPtrVec.push_back(itemPtr);
				/// 初回の配置のみ切り替え
				if (name == Title) { name = Menu; }
			}
		}
		else
		{
			TimeM().ChangeGameSpeedSlower(false);
		}
		/// 後でアクティブに
		/// MHandle = -1;
	}

	/// 保持している場合
	if (holdItem)
	{
		DrawDebugGrid();
		/// マスに置こうとしているか調べる
		CheckInGrid(mouseWorldPos);
		/// モデルの描画
		/// inGrid-> 座標を補正する
		VECTOR drawPos = mouseWorldPos;
		if (inGrid)
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

	if (!itemPtrVec.empty())
	{
		for (int i = 0; i < itemPtrVec.size(); i++)
		{
			itemPtrVec[i]->Update();
		}
	}

	DrawPolygonIndexed3D(vertices, 4, index, 2, mapTexture, TRUE);
}
/// <summary>
/// カメラの移動に応じて描画範囲を変更できるようにする
/// </summary>
void Map::Update()
{
	Draw();
	if(GameM().TerrainInfoChanged())
	{
		Reload();
	}
}

void Map::Update(SceneName& sequence)
{
	Draw(sequence);
}

void Map::AddStart(Vector2Int pos)
{
	Box* startPtr = new Box();
	VECTOR VecPos = startPtr->GetBoxCenterPos(pos.y, pos.x);
	startPtr->Init(VecPos, Tag::Start);
	startPtrVec.push_back(startPtr); //! スマートポインタの場合は所有権を移動させる
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

/// マウスのワールド座標取得
/// ワールド座標のyは0とする
///VECTOR ConvScreenPosToWorldPos_ZLinear()
/// マウスからレイを飛ばして0になるまで調べる

VECTOR Map::GetMouseWorldPos()
{
	MouseInfo mouseInfo = Input().GetMouseInfo();
	VECTOR mouseWorldPos = ConvScreenPosToWorldPos(VGet(mouseInfo.position.x, mouseInfo.position.y, 0.5f));
	mouseWorldPos = Round(mouseWorldPos);
	VECTOR rayDir = VNorm(VSub(mouseWorldPos, GameM().GetCameraPosition()));
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
void Map::CheckInGrid(VECTOR& mousePos)
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

void Map::DrawDebugGrid()
{
	/// マップのグリッド線を表示
	int XAxizcolor = GetColor(255, 255, 255);
	int ZAxizColor = GetColor(255, 255, 255);
	/// デバッグ
	if (mapInfo.height == -1)
	{
		for (int z = 0; z <= MAP_UNIT * 10; z += MAP_UNIT)
		{
			DrawLine3D(VGet(0, 0, z), VGet(MAP_UNIT * 10, 0, z), XAxizcolor);
		}

		for (int x = 0; x <= MAP_UNIT * 10; x += MAP_UNIT)
		{
			DrawLine3D(VGet(x, 0, 0), VGet(x, 0, MAP_UNIT * 10), ZAxizColor);
		}
	}
	else
	{
		int outLineColor = GetColor(255, 255, 255);
		/// 外枠の描画
		DrawLine3D(VGet(0, 0, 0), VGet(mapInfo.width * MAP_UNIT + 0, 0, 0), outLineColor);
		DrawLine3D(VGet(0, 0, mapInfo.height * MAP_UNIT), VGet(mapInfo.width * MAP_UNIT, 0, mapInfo.height * MAP_UNIT), outLineColor);
		DrawLine3D(VGet(0, 0, 0), VGet(0, 0, mapInfo.height * MAP_UNIT), outLineColor);
		DrawLine3D(VGet(mapInfo.width * MAP_UNIT, 0, 0), VGet(mapInfo.width * MAP_UNIT, 0, mapInfo.height * MAP_UNIT), outLineColor);

		//z軸
		for (int x = 1; x < mapInfo.width; x++)
		{
			DrawLine3D(VGet(x * MAP_UNIT, 0, 0), VGet(x * MAP_UNIT, 0, mapInfo.height * MAP_UNIT), ZAxizColor);
		}

		//x軸
		for (int z = 1; z < mapInfo.height; z++)
		{
			DrawLine3D(VGet(0, 0, z * MAP_UNIT), VGet(mapInfo.width * MAP_UNIT, 0, z * MAP_UNIT), XAxizcolor);
		}
	}
}
