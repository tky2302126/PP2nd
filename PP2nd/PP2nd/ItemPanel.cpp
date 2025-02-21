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

void ItemPanel::Init(int index, int& _GH, ItemInfo& _info)
{
	start.x = index * HUD_ITEM_SIZE;
	start.y = WINDOW_HEIGHT - HUD_ITEM_SIZE;
	end.x = start.x + HUD_ITEM_SIZE + 1;
	end.y = WINDOW_HEIGHT;

	GH = _GH;
	info = _info;
}

void ItemPanel::Init(int index, int& _GH, ItemInfo& _info, std::function<void(TerrainList name)>& function)
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
	MouseInfo currentInput = InputSystem::GetInstance().GetMouseInfo();
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
	/// rect内でクリック&&!selected -> selected
	if(CheckInRect(currentInput.position,start,end) && !selected)
	{
		selected = true;
		TimeManager::GetInstance().ChangeGameSpeedSlower(true);
	}

	/// rect内でクリック&& selected -> !selected
	else if (CheckInRect(currentInput.position, start, end) && selected)
	{
		selected = false;
		TimeManager::GetInstance().ChangeGameSpeedSlower(false);
	}
	/// rect外でクリック&& selected -> !selected
	else if (!CheckInRect(currentInput.position, start, end) && selected)
	{
		selected = false;
		TimeManager::GetInstance().ChangeGameSpeedSlower(false);
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
