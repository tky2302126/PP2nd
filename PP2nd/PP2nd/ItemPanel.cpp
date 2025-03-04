#include "ItemPanel.h"

void ItemPanel::Init(int index, int _GH, ItemInfo& _info, std::function<void(TerrainList name)>& function)
{
	start.x = index * HUD_ITEM_SIZE;
	start.y = WINDOW_HEIGHT - HUD_ITEM_SIZE;
	end.x = start.x + HUD_ITEM_SIZE + 1;
	end.y = WINDOW_HEIGHT;

	GH = _GH;
	info = _info;
	cbFunction = function;
}

void ItemPanel::UnInit()
{
	cbFunction = nullptr;
}

void ItemPanel::Update()
{
	if(selected)
	{
		DrawExtendGraph(start.x, start.y-ITEMPANEL_SELECTED, end.x, end.y-ITEMPANEL_SELECTED, GH, false);
		DrawFormatString(start.x, start.y - ITEMPANEL_SELECTED, GetColor(255, 255, 255), "×%d", info.num);
	}
	else
	{
		DrawExtendGraph(start.x, start.y, end.x, end.y, GH, false);
		DrawFormatString(start.x,start.y,GetColor(255,255,255),"×%d",info.num);
	}

	/// InputSystemの監視
	MouseInfo currentInput = Input().GetMouseInfo();
	/// ホールドしたアイテムがHUDの範囲を抜けたとき、Mapに通知
	if(selected && currentInput.state.left ==Performed &&currentInput.position.y<start.y)
	{
		if(cbFunction)
		{
			cbFunction(info.name);
		}
		selected = false;
	}

	if (currentInput.state.left != Started) { return; }

	bool isInside = CheckInRect(currentInput.position, start, end);
	/// rect内でクリック&&!selected -> selected
	if(isInside && !selected)
	{
		selected = true;
		TM().ChangeGameSpeedSlower(true);
	}

	/// rect内でクリック&& selected -> !selected
	else if (isInside && selected)
	{
		selected = false;
		TM().ChangeGameSpeedSlower(false);
	}
	/// rect外でクリック&& selected -> !selected
	else if (!isInside && selected)
	{
		selected = false;
		TM().ChangeGameSpeedSlower(false);
	}
	
}

void ItemPanel::Decrease()
{
	info.num--;
}

void ItemPanel::SetIndex(int index)
{
	start.x = index * HUD_ITEM_SIZE;
	start.y = WINDOW_HEIGHT - HUD_ITEM_SIZE;
	end.x = start.x + HUD_ITEM_SIZE + 1;
	end.y = WINDOW_HEIGHT;
}
