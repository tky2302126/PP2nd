#pragma once
#include "define.h"
#include "manager.h"
class Box;
/// <summary>
/// MVPに分割したい
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Init();
	void Init(const _mapInfo& mapInfo);
	void UnInit();

	void Load(int);
	void RegistHoldItem(TerrainList name);
	void Draw();
	void Update();

private:
	void LoadTerrainInfo(int);
	void LoadMapInfo(int);
	VECTOR GetMouseWorldPos();
	void CHeckInGrid(VECTOR& mousePos);
private:
	TerrainList holdItemTag = TerrainList::None;
	vector<vector<int>> terrainInfo;
	_mapInfo mapInfo;
	UniquePtr<Box> goalUPtr;
	bool holdItem= false;
	bool inGrid = false;
	int MHandle = -1;
};

