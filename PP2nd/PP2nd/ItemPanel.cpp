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

	StringBuilder sb;
	switch (info.name)
	{
	case TerrainList::CUBE:
		sb.append("敵の進路を妨害する\n").append("進路をすべてふさぐと破壊される");
		break;

	case TerrainList::DECOY:
		sb.append("敵をひきつける効果を持つ\n").append("敵にある程度攻撃されると壊れる");
		break;
	default:
		break;
	}
	summaryText = sb.toString();
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
		ShowSummary();
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
		TimeM().ChangeGameSpeedSlower(true);
	}

	/// rect内でクリック&& selected -> !selected
	else if (isInside && selected)
	{
		selected = false;
		TimeM().ChangeGameSpeedSlower(false);
	}
	/// rect外でクリック&& selected -> !selected
	else if (!isInside && selected)
	{
		selected = false;
		TimeM().ChangeGameSpeedSlower(false);
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

/// <summary>
/// 選択時に説明を表示する
/// </summary>
void ItemPanel::ShowSummary()
{

	RECTInt summaryBox = 
	{
		WINDOW_HEIGHT - HUD_ITEM_SIZE - ITEMPANEL_SELECTED - ITEM_SUMMARY_HEIGHT,
		WINDOW_HEIGHT - HUD_ITEM_SIZE - ITEMPANEL_SELECTED ,
		WINDOW_WIDTH/2 - ITEM_SUMMARY_WIDTH,
		WINDOW_WIDTH/2 + ITEM_SUMMARY_WIDTH
	};
	DrawBox(summaryBox.left, summaryBox.top, summaryBox.right, summaryBox.bottom,GetColor(0,0,0),true);
	DrawFormatString(summaryBox.left+5, summaryBox.top+5, GetColor(255, 255, 255), summaryText.c_str());
}
