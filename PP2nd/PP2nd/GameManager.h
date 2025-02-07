#pragma once
#include "define.h"
#include "Item.h"

/// <summary>
/// メインループの進行を管理
/// 必要なデータを保持、受け渡しの役割を想定
/// todo マップ情報を読み取り、保存する
/// </summary>


class GameManager
{
public:
	GameManager();
	~GameManager();

	void Load();
	void Init();
	void UnInit();
	HandleData LoadHandleData(HDKey key);
	HandleData& GetHandleData(HDKey key);
	void SetItemInfo(ItemInfo info);
	const unordered_map<TerrainList, int>& GetItemInfoUnMap() const;
	int& GetItemNum(TerrainList name);
	static GameManager& GetInstance();
	void SetCameraPosition(VECTOR pos);
	VECTOR GetCameraPosition();
	vector<vector<TerrainList>> GetTerrainInfo() const;
	_mapInfo GetMapInfo() const;
	void AddTerrainInfo(TerrainList name, VECTOR pos);
	void AddTerrainInfo(TerrainList name, Vector2Int pos);
	void RemoveTerrainInfo(VECTOR pos);
	void LoadTerrainInfo(int day);
	void InitTerrainInfo(int width, int height);
	void LoadTest();
	void UseItem(TerrainList name);
	bool ItemInfoChanged() { return itemInfoChanged; }
	void CheckedItemInfo() { itemInfoChanged = false; }
	void SequenceProceed() { currentSequence = Battle; }
	void GameOver();
	void GameClear();
	bool IsGameOver() const { return isGameOver; }
	bool IsGameClear() const { return isGameClear; }
	Sequence CurrentSequence() const { return currentSequence; }
private:
	unmap<HDKey, HandleData> handleDatas;
	unmap<TerrainList,int> itemInfo; /// 所有しているアイテム
	static UniquePtr<GameManager> Instance;
	VECTOR cameraPos = VECTOR();
	_mapInfo mapInfo = _mapInfo(); /// メインループのマップ情報
	vector<vector<TerrainList>> terrainInfo = vector<vector<TerrainList>>();
	bool itemInfoChanged = false;
	bool isGameOver = false;
	bool isGameClear = false;
	Sequence currentSequence = SetUp;
};

