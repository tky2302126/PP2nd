#pragma once
#include "define.h"
#include "Item.h"
/// <summary>
/// メインループの進行を管理
/// 必要なデータを保持、受け渡しの役割を想定
/// </summary>

enum ItemList
{
	Cube,
	ALL
};

struct HandleData
{
	int GHandle;
	int MHandle;
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Load();
	void Init();
	void UnInit();

	static GameManager& GetInstance();

private:

	vector<HandleData> handleInfo;

	static UniquePtr<GameManager> Instance;
};

