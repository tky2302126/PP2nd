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
	void Reload();
	void RegistHoldItem(TerrainList name);
	void Draw();
	void Draw(SceneName&);
	void Update();
	void Update(SceneName&);

	void AddStart(Vector2Int pos);
	void AddGoal(Vector2Int pos);
	void RemoveItemPtr(Item* _item);
private:
	void LoadTerrainInfo(int);
	void LoadMapInfo(int);
	VECTOR GetMouseWorldPos();
	void CheckInGrid(VECTOR& mousePos);
	void DrawDebugGrid();
private:
	TerrainList holdItemTag = TerrainList::None;
	std::vector<Item*> itemPtrVec;
	_mapInfo mapInfo;
	UniquePtr<Box> goalUPtr;
	std::vector<Box*> startPtrVec;
	bool holdItem= false;
	bool inGrid = false;
	int MHandle = -1;
	int mapTexture = -1;
	VERTEX3D vertices[4] =
	{
		{VGet(MAP_UNIT * -30, -10, MAP_UNIT *  30), VGet(0, 1, 0),GetColorU8(255, 255, 255, 255), GetColorU8(0, 0, 0,0), 0.0f, 0.0f, 0.0f,0.0f}, // 左上
		{VGet(MAP_UNIT *  30, -10, MAP_UNIT *  30), VGet(0, 1, 0),GetColorU8(255, 255, 255, 255), GetColorU8(0, 0, 0,0), 1.0f, 0.0f, 0.0f, 0.0f}, // 右上
		{VGet(MAP_UNIT * -30, -10, MAP_UNIT * -30), VGet(0, 1, 0),GetColorU8(255, 255, 255, 255), GetColorU8(0, 0, 0,0), 0.0f, 1.0f, 0.0f, 0.0f}, // 左下
		{VGet(MAP_UNIT *  30, -10, MAP_UNIT * -30), VGet(0, 1, 0),GetColorU8(255, 255, 255, 255), GetColorU8(0, 0, 0,0), 1.0f, 1.0f, 0.0f, 0.0f}  // 右下
	};

	WORD index[6] = { 0, 1, 2, 1, 3, 2 };

	int baseTex;
	int normalTex;
	int aoTex;
	int roughnessTex;
	int shaderHandle;
};

