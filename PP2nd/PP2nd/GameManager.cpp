#include "GameManager.h"

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
	HandleData buff;
	fs::path GHandlePath = "./Resource/cube.png";
	string GHandlePathString = GHandlePath.string();
	fs::path MHandlePath = "./Resource/stone.mv1";
	string MHandlePathString = MHandlePath.string();
	buff.GHandle = LoadGraph(GHandlePathString.c_str());
	buff.MHandle = MV1LoadModel(MHandlePathString.c_str());
	handleDatas[HDKey::Cube] = buff ;

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


	return HandleData();
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

void GameManager::SetItemInfo(ItemInfo info)
{
	itemInfo[info.name] = info.num;
}

const unordered_map<TerrainList,int>& GameManager::GetItemInfoUnMap() const
{
	return itemInfo;
}

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

void GameManager::SetCameraPosition(VECTOR pos)
{
	cameraPos = pos;
}

VECTOR GameManager::GetCameraPosition()
{
	return cameraPos;
}
