#include "ItemPanel.h"

/// <summary>
/// 
/// </summary>
/// <param name="index"></param>
/// <param name="GH"></param>
/// <param name="num"></param>
void ItemPanel::Init(int index, int& _GH, int& _num)
{
	start.x = index * HUD_ITEM_SIZE;
	start.y = WINDOW_HEIGHT - HUD_ITEM_SIZE;
	end.x = start.x + HUD_ITEM_SIZE + 1;
	end.y = WINDOW_HEIGHT;

	GH = _GH;
	num = _num;
}

void ItemPanel::UnInit()
{
}

void ItemPanel::Update()
{
	if(selected)
	{
		DrawExtendGraph(start.x, start.y+ITEMPANEL_SELECTED, end.x, end.y+ITEMPANEL_SELECTED, GH, false);
	}
	else
	{
		DrawExtendGraph(start.x, start.y, end.x, end.y, GH, false);
	}

	/// InputSystemの監視
	/// rect内でクリック&&!selected -> selected
	/// rect内でクリック&& selected -> !selected
	/// rect外でクリック&& selected -> !selected
	/// 設置時のイベントでselected -> !selected
	
}

void ItemPanel::Decrease()
{
}

void ItemPanel::SetIndex(int index)
{
}
