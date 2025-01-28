#pragma once
#include "define.h"
#include "Item.h"

/// <summary>
/// メインループの進行を管理
/// 必要なデータを保持、受け渡しの役割を想定
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
	void AddTerrainInfo(TerrainList name, VECTOR pos);
	void LoadTerrainInfo(int day);
	void InitTerrainInfo(int width, int height);
private:
	unmap<HDKey, HandleData> handleDatas;
	unmap<TerrainList,int> itemInfo;
	static UniquePtr<GameManager> Instance;
	bool holdItem= false;
	VECTOR cameraPos = VECTOR();
	vector<vector<TerrainList>> terrainInfo = vector<vector<TerrainList>>();
};

