#include "HUD.h"

HUD::HUD()
	:centerPos(0),fontHandle(-1),timerPanelRect(),playGH(-1),pauseGH(-1),fastGH(-1),optionGH(-1),textHeight(0),textWidth(0),fast(false)
{
}

HUD::~HUD()
{
	DeleteFontToHandle(fontHandle);
}

void HUD::Init()
{
	/// パスを作成
	string executablePath = GetExecutablePath();
	string fontPath = executablePath + "\\Resource\\GAGAGAGA-FREE.otf";

	/// フォントデータを一時的に取り込み
	AddFontResourceExA(fontPath.c_str(), FR_PRIVATE, NULL);

	/// 時間の表示
	fontHandle = CreateFontToHandle("GAGAGAGA FREE", 48, 3, DX_FONTTYPE_ANTIALIASING);
	const char* text = "00:00";
	GetDrawStringSizeToHandle(&textWidth, &textHeight, NULL, text, strlen(text), fontHandle);
	centerPos = (WINDOW_WIDTH - textWidth) / 2;
	timerPanelRect.left = centerPos;
	timerPanelRect.top = 0;
	timerPanelRect.right = centerPos + textWidth;
	timerPanelRect.bottom = textHeight;
	
	/// HUDパネルの準備

}


void HUD::SetCallback(function<void(TerrainList)> cb)
{
	callback = cb;
	/// UIスプライトの読みこみ
	Load();
}

void HUD::UnInit()
{

}

/// <summary>
/// イニシャライズのときに下部パネル情報をロードする
/// </summary>
void HUD::Load()
{
	unordered_map<TerrainList,int> ItemInfoUnMap = GameManager::GetInstance().GetItemInfoUnMap();
	if(!ItemInfoUnMap.empty())
	{
		int index = 0;
		for(int i=0;i<(int)TerrainList::ItemAll;i++)
		{
			auto it = ItemInfoUnMap.find((TerrainList)i);
			if(it != ItemInfoUnMap.end())
			{
				ItemPanel* itemPanelPtr = new ItemPanel();
				HDKey key = (HDKey)((int)HDKey::Cube + i);
				///! ここ直す
				int GH = GameManager::GetInstance().GetHandleData(key).GHandle;
				ItemInfo currentInfo;
				currentInfo.name = (TerrainList)i;
				currentInfo.num = ItemInfoUnMap[(TerrainList)i];
				int num = ItemInfoUnMap[(TerrainList)i];
				// itemPanelPtr->Init(index, GH, num);
				itemPanelPtr->Init(index, GH, currentInfo,callback);
				index++;
				itemPanelMap[(TerrainList)i] = itemPanelPtr;
			}
		}
	}
}

/// <summary>
/// アイテムを使用して更新が必要な場合、実行する
/// 使用した通知はGameManagerから受ける(オブザーバーパターン)
/// </summary>
void HUD::ReLoad()
{
	/// num==0の場合、破棄
}

void HUD::Draw()
{
	DrawBox(timerPanelRect.left, timerPanelRect.top, timerPanelRect.right, timerPanelRect.bottom, GetColor(128, 128, 128), TRUE);

	DrawStringToHandle(centerPos, 0, "00:00", GetColor(255, 255, 255), fontHandle);

	/// アイテムの表示
	//int drawCount = 0;
	//for(int i=0;i<ItemList::ALL;i++)
	//{
	//	// 所持していたら描画
	//	if(GameManager::GetInstance().GetItemNum((ItemList)i)>0)
	//	{
	//		DrawExtendGraph(drawCount*HUD_ITEM_SIZE,WINDOW_HEIGHT- HUD_ITEM_SIZE,(drawCount+1)*HUD_ITEM_SIZE+1,WINDOW_HEIGHT,itemGH[(ItemList)i],false);
	//		drawCount++;
	//	}
	//}
	if(!itemPanelMap.empty())
	{
		TerrainList current = TerrainList::CUBE;
		while (true)
		{
			if (current == TerrainList::ItemAll) { break; }
			if(itemPanelMap[current] != nullptr)
			{
				auto it = itemPanelMap[current];
				it->Update();
			}
			current = (TerrainList)((int)current+ 1);
		}
	}
}

void HUD::Update()
{
	Draw();
}
/// <summary>
/// 時間の更新を実行するUpdate
/// </summary>
/// <param name="remainTime"></param>
void HUD::Update(int remainTime)
{
}

/// <summary>
/// 
/// </summary>
void HUD::RegistItem(int)
{
}

void HUD::ExcludeItem(int)
{
}

void HUD::UseItem()
{
}

