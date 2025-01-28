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

void ItemPanel::Init(int index, int& _GH, ItemInfo& _info, function<void(TerrainList name)>& function)
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
	}
	else
	{
		DrawExtendGraph(start.x, start.y, end.x, end.y, GH, false);
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
	if(ClickInRect(currentInput) && !selected)
	{
		selected = true;
		/// GameManagerにHoldItemの情報を通知
	}

	/// rect内でクリック&& selected -> !selected
	else if (ClickInRect(currentInput) && selected)
	{
		selected = false;
		/// GameManagerにHoldItemの情報を通知
	}
	/// rect外でクリック&& selected -> !selected
	else if (!ClickInRect(currentInput) && selected)
	{
		selected = false;
		/// GameManagerにHoldItemの情報を通知
	}

	/// 設置時のイベントでselected -> !selected <-不要かも？
	
}

void ItemPanel::Decrease()
{
}

void ItemPanel::SetIndex(int index)
{
}

bool ItemPanel::ClickInRect(MouseInfo& input)
{
	return input.position.y >= start.y && input.position.x >= start.x && input.position.x <= end.x && input.state.left == Started;
}
