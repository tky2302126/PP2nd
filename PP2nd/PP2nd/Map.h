#pragma once
#include "define.h"
#include "manager.h"
#include "Item.h"
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

	void AddStart(Vector2Int pos);
	void AddGoal(Vector2Int pos);

private:
	void LoadTerrainInfo(int);
	void LoadMapInfo(int);
	VECTOR GetMouseWorldPos();
	void CHeckInGrid(VECTOR& mousePos);
private:
	TerrainList holdItemTag = TerrainList::None;
	vector<Item*> itemPtrVec;
	_mapInfo mapInfo;
	UniquePtr<Box> goalUPtr;
	vector<Box*> startPtrVec;
	bool holdItem= false;
	bool inGrid = false;
	int MHandle = -1;
};

