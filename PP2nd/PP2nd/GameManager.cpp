#include "GameManager.h"
#include "EnemyManager.h"
#include "Item.h"

UniquePtr<GameManager> GameManager::Instance = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

/// <summary>
/// スプライトデータとモデルデータの読み込み
/// csvか何かにまとめる
/// </summary>
void GameManager::Load()
{
#pragma region デバッグ用
	HandleData Cube;
	fs::path GHandlePath = "./Resource/cube.png";
	string GHandlePathString = GHandlePath.string();
	fs::path MHandlePath = "./Resource/stone.mv1";
	string MHandlePathString = MHandlePath.string();
	Cube.GHandle = LoadGraph(GHandlePathString.c_str());
	Cube.MHandle = MV1LoadModel(MHandlePathString.c_str());
	handleDatas[HDKey::Cube] = Cube ;

	HandleData check{};
	GHandlePath = "./Resource/check-mark.png";
	GHandlePathString = GHandlePath.string();
	check.GHandle = LoadGraph(GHandlePathString.c_str());
	check.MHandle = -1;
	handleDatas[HDKey::Check] = check;
	
	HandleData cross{};
	GHandlePath = "./Resource/cancel.png";
	GHandlePathString = GHandlePath.string();
	cross.GHandle = LoadGraph(GHandlePathString.c_str());
	cross.MHandle = -1;
	handleDatas[HDKey::Cross] = cross;

	Item::gHandleCheck = handleDatas[HDKey::Check].GHandle;
	Item::gHandleCross = handleDatas[HDKey::Cross].GHandle;

#pragma endregion

	for(int i=0;i<(int)TerrainList::ItemAll;i++)
	{
		
	}
}

void GameManager::Init()
{
	Load();
}

void GameManager::UnInit()
{
}

/// <summary>
/// 必要に応じて読み込む
/// </summary>
/// <param name="key"> 検索用のキー</param>
/// <returns></returns>
HandleData GameManager::LoadHandleData(HDKey key)
{
	return handleDatas[key];
}

HandleData& GameManager::GetHandleData(HDKey key)
{
	auto it = handleDatas.find(key);
	/// 見つからなかった場合
	if(it ==handleDatas.end())
	{
		HandleData data = LoadHandleData(key);
		handleDatas[key] = data;
		return handleDatas.at(key);
	}
		return it->second;
}
/// <summary>
/// アイテムの生産・消費が行われたときに増減させる
/// 
/// </summary>
/// <param name="info"></param>
void GameManager::SetItemInfo(ItemInfo info)
{
	itemInfo[info.name] = info.num;
}
/// <summary>
/// アイテム所持情報を参照
/// </summary>
/// <returns></returns>
const unordered_map<TerrainList,int>& GameManager::GetItemInfoUnMap() const
{
	return itemInfo;
}

/// <summary>
/// アイテム所持数を参照
/// いらなそう
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
int& GameManager::GetItemNum(TerrainList name)
{
	auto it = itemInfo.find(name);
	if(it == itemInfo.end())
	{
		int null = 0;
		return null;
	}
	return it->second;
}

GameManager& GameManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = make_unique<GameManager>();
	}
	return *Instance;
}

/// <summary>
/// アプリケーション実行中のカメラの位置を保持する
/// </summary>
/// <param name="pos"></param>
void GameManager::SetCameraPosition(VECTOR pos)
{
	cameraPos = pos;
}
/// <summary>
/// カメラの位置を参照
/// </summary>
/// <returns></returns>
VECTOR GameManager::GetCameraPosition()
{
	return cameraPos;
}

vector<vector<TerrainList>> GameManager::GetTerrainInfo() const
{
	return terrainInfo ;
}

_mapInfo GameManager::GetMapInfo() const
{
	return mapInfo;
}

/// <summary>
/// 追加地形情報を更新する
/// </summary>
/// <param name="name"></param>
/// <param name="pos"></param>
void GameManager::AddTerrainInfo(TerrainList name, VECTOR pos)
{
	int row = floor(pos.z / MAP_UNIT);
	int col = floor(pos.x / MAP_UNIT);

	terrainInfo[row][col] = name;
	///更新したら通知する
	EnemyManager::GetInstance().ReCalculateRoute();
}

/// <summary>
/// 地形情報を追加する
/// </summary>
/// <param name="name"></param>
/// <param name="pos"></param>
void GameManager::AddTerrainInfo(TerrainList name, Vector2Int pos)
{
	terrainInfo[pos.y][pos.x] = name;
}

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
void GameManager::RemoveTerrainInfo(VECTOR pos)
{
	int row = floor(pos.z / MAP_UNIT);
	int col = floor(pos.x / MAP_UNIT);

	terrainInfo[row][col] = TerrainList::None;

	///更新したら通知する
	EnemyManager::GetInstance().ReCalculateRoute();
}

/// <summary>
/// csvファイル等から地形情報を取得する
/// </summary>
/// <param name="day"></param>
void GameManager::LoadTerrainInfo(int day)
{

}

/// <summary>
/// 地形情報を初期化する
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void GameManager::InitTerrainInfo(int width, int height)
{
	terrainInfo.resize(height, vector<TerrainList>(width, TerrainList::None));
}

void GameManager::LoadTest()
{
	_mapInfo testMap(21, 9, 10, 4);
	InitTerrainInfo(testMap.width, testMap.height);
	Vector2Int goalPoint = { testMap.goalWidth,testMap.goalHeight };
	AddTerrainInfo(TerrainList::Goal, goalPoint);
	mapInfo = testMap;
	ItemInfo buff;
	buff.name = TerrainList::CUBE;
	buff.num = 20;
	SetItemInfo(buff);
}

void GameManager::UseItem(TerrainList name)
{
	itemInfo[name]--;
	itemInfoChanged = true;
}

/// <summary>
/// ゲームオーバー処理
/// </summary>
void GameManager::GameOver()
{
	isGameOver = true;
	currentSequence = Result;
}

/// <summary>
/// クリア処理
/// </summary>
void GameManager::GameClear()
{
	isGameClear = true;
	currentSequence = Result;
}
