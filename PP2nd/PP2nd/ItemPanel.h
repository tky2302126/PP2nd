#pragma once
#include "define.h"
#include "manager.h"

/// <summary>
/// HUDに表示するアイテムパネル
/// </summary>
class ItemPanel
{
public:
	void Init(int _index,int _GH, ItemInfo& _info, std::function<void(TerrainList name)>& cbfunction);
	void UnInit();
	void Update();
	void Decrease();
	void SetIndex(int index);
	int GetNum() { return info.num; }
private:
	int GH;
	ItemInfo info;
	bool selected = false; // 選択フラグ
	bool placed = false;   // 設置フラグ
	Vector2Int start; // 左上
	Vector2Int end;	  // 右下
	std::function<void(TerrainList name)> cbFunction; // コールバック関数
};

