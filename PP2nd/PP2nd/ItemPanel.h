#pragma once
#include "define.h"
#include "manager.h"

/// <summary>
/// HUDに表示するアイテムパネル
/// </summary>
class ItemPanel
{
public:
	void Init(int index,int& GH, int& num);
	void Init(int _index,int& _GH, ItemInfo& _info);
	void Init(int _index,int& _GH, ItemInfo& _info, function<void(ItemList name)>& cbfunction);
	void UnInit();
	void Update();
	void Decrease();
	void SetIndex(int index);
private:
	int GH;
	ItemInfo info;
	int num;
	bool selected = false; // 選択フラグ
	bool placed = false;   // 設置フラグ
	Vector2Int start;
	Vector2Int end;
	function<void(ItemList name)> cbFunction;

	bool ClickInRect(MouseInfo& input);
};

