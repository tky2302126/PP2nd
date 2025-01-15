#pragma once
#include "define.h"

class Map
{
public:
	Map();
	~Map();

	void Init();
	void UnInit();

	void Load(int);
	void Draw();
	void Update();

private:
	void LoadTerrainInfo(int);
	void LoadMapInfo(int);

private:
	int height;
	int width;
	vector<vector<int>> terrainInfo;
	_mapInfo mapInfo;


};

