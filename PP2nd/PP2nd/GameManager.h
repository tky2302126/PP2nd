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
	const unordered_map<ItemList, int>& GetItemInfo() const;
	int& GetItemNum(ItemList name);
	static GameManager& GetInstance();

private:
	unmap<HDKey, HandleData> handleDatas;
	unmap<ItemList,int> itemInfo;
	static UniquePtr<GameManager> Instance;
};

