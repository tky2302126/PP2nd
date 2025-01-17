#pragma once
#include "define.h"

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
	void Draw();
	void Update();

private:
	void LoadTerrainInfo(int);
	void LoadMapInfo(int);

private:
	vector<vector<int>> terrainInfo;
	_mapInfo mapInfo;
	int margin;
	UniquePtr<Box> goalUPtr;
};

