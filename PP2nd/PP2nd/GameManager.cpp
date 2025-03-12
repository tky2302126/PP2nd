#include "GameManager.h"
#include "EnemyManager.h"
#include "AudioManager.h"
#include "TimeManager.h"
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
	std::string GHandlePathString = GHandlePath.string();
	fs::path MHandlePath = "./Resource/stone.mv1";
	std::string MHandlePathString = MHandlePath.string();
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

	HandleData Decoy;
	GHandlePath = "./Resource/scarecrow.png";
	GHandlePathString = GHandlePath.string();
	MHandlePath = "./Resource/scarecrow.mv1";
	MHandlePathString = MHandlePath.string();
	Decoy.GHandle = LoadGraph(GHandlePathString.c_str());
	Decoy.MHandle = MV1LoadModel(MHandlePathString.c_str());
	handleDatas[HDKey::Decoy] = Decoy;

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
const std::unordered_map<TerrainList,int>& GameManager::GetItemInfoUnMap() const
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
		int num = -1;
		return num;
	}
	return it->second;
}

GameManager& GameManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = std::make_unique<GameManager>();
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

std::vector<std::vector<TerrainList>> GameManager::GetTerrainInfo() const
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
	int row = static_cast<int>(floor(pos.z / MAP_UNIT));
	int col = static_cast<int>(floor(pos.x / MAP_UNIT)) ;

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
/// 地形情報を破壊する
/// 敵の攻撃で呼ばれる想定
/// </summary>
/// <param name="pos"></param>
/// <param name="damage"></param>
void GameManager::DamageTerrainInfo(VECTOR pos, int damage = -1)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
void GameManager::RemoveTerrainInfo(VECTOR pos)
{
	int row = static_cast<int>(floor(pos.z / MAP_UNIT));
	int col = static_cast<int>(floor(pos.x / MAP_UNIT));
	if (terrainInfo.empty()) return;
	terrainInfo[row][col] = TerrainList::None;

	///更新したら通知する
	EnemyManager::GetInstance().ReCalculateRoute();
	terrainInfoChanged = true;

}

/// <summary>
/// csvファイル等から地形情報を取得する
/// </summary>
/// <param name="day"></param>
void GameManager::LoadStageInfo(const std::string& fileName)
{
	std::ifstream inFile(fileName, std::ios::in);

	if (!inFile)
	{
		printfDx("ファイルの読み込みに失敗");
		return;
	}

	std::string line;
	char comma = ','; // コンマを無視するための変数

	// mapInfoの読み込み
	if (std::getline(inFile, line) && line == "mapInfo :")
	{
		std::getline(inFile, line); // mapInfoの値を読み込む
		std::istringstream mapStream(line); 
		mapStream >> mapInfo.height >> comma >> mapInfo.width >> comma >> mapInfo.goalHeight >> comma >> mapInfo.goalWidth;
	}

	// terrainInfoの読み込み
	if (std::getline(inFile, line) && line == "terrainInfo :")
	{
		InitTerrainInfo(mapInfo.width, mapInfo.height);  // 既存のterrain情報をクリア
		while (std::getline(inFile, line))
		{
			if (line.empty()) break;
			std::istringstream terrainStream(line);
			int y, x;
			int terrainType;
			terrainStream >> y >> comma >> x >> comma >> terrainType;
			if (terrainStream)
			{
				if (y >= 0 && y < terrainInfo.size() && x >= 0 && x < terrainInfo[y].size())
				{
					terrainInfo[y][x] = static_cast<TerrainList>(terrainType);
				}
			}
		}
	}

	// startPosの読み込み
	if (std::getline(inFile, line) && line == "startPos :")
	{
		std::vector<Vector2Int> startVec;
		while (std::getline(inFile, line))
		{
			if (line.empty()) break;
			std::istringstream startStream(line);
			int y, x;
			startStream >> y >> comma >> x;
			if (startStream)
			{
				startVec.push_back({ y, x });
			}
		}

		// enemymanagerに渡す
		EnemyManager::GetInstance().SetStartPos(startVec);
	}

	// ItemInfoの読み込み
	if (std::getline(inFile, line) && line == "ItemInfo :")
	{
		itemInfo.clear();  // 既存のitemInfo情報をクリア
		while (std::getline(inFile, line))
		{
			if (line.empty()) break;
			std::istringstream itemStream(line);
			int key, value;
			itemStream >> key >> comma >> value;
			if (itemStream)
			{
				itemInfo[static_cast<TerrainList>(key)] = value;
			}
		}
	}

	if(std::getline(inFile, line) && line == "TimeLine :")
	{
		std::vector<TimeLine> timeLineVec;
		while (std::getline(inFile, line))
		{
			if (line.empty()) break;
			std::istringstream TLStream(line);
			int time, x, y, type;
			TLStream >> time >> comma >> x >> comma >> y >> comma >> type;
			if (TLStream)
			{
				TimeLine temp = { time, {x, y},(EnemyList)type };
				timeLineVec.push_back(temp);
			}
		}

		/// timemanagerに渡す
		TimeManager::GetInstance().SetTimeLine(timeLineVec);
	}

	// ファイルを閉じる
	inFile.close();
	// printfDx("ファイルの読み込み完了");
}

/// <summary>
/// 地形情報を初期化する
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void GameManager::InitTerrainInfo(int width, int height)
{
	if (!terrainInfo.empty()) { terrainInfo.clear(); }
	terrainInfo.resize(height, std::vector<TerrainList>(width, TerrainList::None));
}

void GameManager::Load(std::string fileName)
{
	LoadStageInfo(fileName);
}

void GameManager::LoadTest()
{
	// LoadStageInfo("Trial_Easy.txt");

#pragma region ステージエディット用
	 _mapInfo testMap(10, 10, 0, 0);
	 InitTerrainInfo(testMap.width, testMap.height);
	 Vector2Int goalPoint = { testMap.goalWidth,testMap.goalHeight };
	 AddTerrainInfo(TerrainList::Goal, goalPoint);
	 mapInfo = testMap;
	 ItemInfo buff;
	 buff.name = TerrainList::CUBE;
	 buff.num = 99;
	 SetItemInfo(buff);
	 ItemInfo buff2;
	 buff2.name = TerrainList::DECOY;
	 buff2.num = 5;
	 SetItemInfo(buff2);
#pragma endregion

}

void GameManager::UseItem(TerrainList name)
{
	itemInfo[name]--;
	itemInfoChanged = true;
}

void GameManager::GameStart()
{
	TimeManager::GetInstance().SetTimer(30);
	currentSequence = SetUp;
}

/// <summary>
/// ゲームオーバー処理
/// </summary>
void GameManager::GameOver()
{
	isGameOver = true;
	currentSequence = Result;
	AudioManager::GetInstance().PlayBGM(BGMList::GAMEOVER, false);
}

/// <summary>
/// クリア処理
/// </summary>
void GameManager::GameClear()
{
	isGameClear = true;
	// 敵をすべて破壊する
	currentSequence = Result;
	AudioManager::GetInstance().PlayBGM(BGMList::GAMECLEAR, false);
}

void GameManager::ExportStageInfo(const std::string& fileName)
{
	std::ofstream outFile(fileName, std::ios::out);

	if(!outFile)
	{
		printfDx("ファイルの作成に失敗");
		return;
	}

	/// mapInfoの出力
	outFile << "mapInfo :\n";
	outFile << mapInfo.height << ",";
	outFile << mapInfo.width << ",";
	outFile << mapInfo.goalHeight << ",";
	outFile << mapInfo.goalWidth ;
	outFile << "\n";
	/// terrainInfoの取得
	outFile << "terrainInfo :\n";
	for(int y =0;y<terrainInfo.size();y++)
	{
		for(int x=0;x<terrainInfo[y].size();x++)
		{
			if(terrainInfo[y][x] != TerrainList::None)
			{
				outFile << y << "," << x << ",";
				outFile << (int)terrainInfo[y][x] << "\n";
			}
		}
	}
	outFile << "\n";
	/// StartをenemyManagerから受け取る

	auto startVec = EnemyManager::GetInstance().GetStartPos();

	outFile << "startPos :\n";
	for(int i=0;i<startVec.size();i++)
	{
		outFile << startVec[i].x << "," << startVec[i].y << "\n";
	}
	outFile << "\n";
	/// ItemInfoの取得
	outFile << "ItemInfo :\n";
	for(const auto&[key, value] : itemInfo)
	{
		outFile << static_cast<int>(key) << "," << value << "\n";
	}
	outFile << "\n";

	/// TimeLineの取得
	outFile << "TimeLine :\n";
	auto timeLine = TimeManager::GetInstance().GetTimeLine();
	for(int i=0; i< timeLine.size();i++)
	{
		outFile << timeLine[i].Time << "," << timeLine[i].startPos.x << "," << timeLine[i].startPos.y << "," << (int)timeLine[i].enemy << "\n";
	}

	/// ファイルで書き出す
	outFile.close();
	printfDx("ファイルの書き出し完了");
}
