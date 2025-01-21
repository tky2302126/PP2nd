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
	/// UIスプライトの読みこみ
	Load();
}

void HUD::UnInit()
{

}

void HUD::Load()
{
	/// アイテムパネルデータのロード
	for(int i=0;i<ItemList::ALL;i++)
	{
		ItemList current = (ItemList)i;
		HDKey key = (HDKey)((int)HDKey::Cube + i);
		HandleData data = GameManager::GetInstance().GetHandleData(key);
		int GH = data.GHandle;
		itemGH[current] = GH;
	}
}

void HUD::Draw()
{
	DrawBox(timerPanelRect.left, timerPanelRect.top, timerPanelRect.right, timerPanelRect.bottom, GetColor(128, 128, 128), TRUE);

	DrawStringToHandle(centerPos, 0, "00:00", GetColor(255, 255, 255), fontHandle);

	/// アイテムの表示
	int drawCount = 0;
	for(int i=0;i<ItemList::ALL;i++)
	{
		// 所持していたら描画
		if(GameManager::GetInstance().GetItemNum((ItemList)i)>0)
		{
			int result = DrawExtendGraph(drawCount*HUD_ITEM_SIZE,WINDOW_HEIGHT- HUD_ITEM_SIZE,(drawCount+1)*HUD_ITEM_SIZE+1,WINDOW_HEIGHT,itemGH[(ItemList)i],false);
			drawCount++;
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
