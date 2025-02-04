#include "HUD.h"

HUD::HUD()
	:centerPos(0),fontHandle(-1),timerPanelRect(),playGH(-1),pauseGH(-1),fastGH(-1),optionGH(-1),textHeight(0),textWidth(0),fast(false)
{
}

HUD::~HUD()
{
	DeleteFontToHandle(fontHandle);
	fs::path basePath = fs::current_path();
	/// OSによって読み込まない？　未検証
	fs::path relativePath = "Resource/GAGAGAGA-FREE.otf";
	fs::path fullPath = basePath / relativePath;
	string fontPath = fullPath.string();
	RemoveFontResourceExA(fontPath.c_str(), FR_PRIVATE, NULL);
}

void HUD::Init()
{
	SetFontCacheToTextureFlag(TRUE);

	/// パスを作成

	fs::path basePath = fs::current_path();
	/// OSによって読み込まない？　未検証
	fs::path relativePath = "Resource/GAGAGAGA-FREE.otf";
	fs::path fullPath = basePath / relativePath;
	string fontPath = fullPath.string();

	/// フォントデータを一時的に取り込み
	int result = AddFontResourceExA(fontPath.c_str(), FR_PRIVATE, NULL);


	/// 時間の表示
	fontHandle = CreateFontToHandle("GAGAGAGA FREE", 48, 3, DX_FONTTYPE_ANTIALIASING);
	const char* text = "00：00";
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
				HDKey key = (HDKey) - 1;
				switch ((TerrainList)i)
				{
				case TerrainList::CUBE:
					key = HDKey::Cube;
						break;
				default:
					
					break;
				}
				int GH = GameManager::GetInstance().GetHandleData(key).GHandle;
				ItemInfo currentInfo;
				currentInfo.name = (TerrainList)i;
				currentInfo.num = ItemInfoUnMap[(TerrainList)i];
				int num = ItemInfoUnMap[(TerrainList)i];
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

	DrawStringToHandle(centerPos, 0, "00：00", GetColor(255, 255, 255), fontHandle);

	/// アイテムの表示
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

void HUD::Draw(int _remainTime)
{
	DrawBox(timerPanelRect.left, timerPanelRect.top, timerPanelRect.right, timerPanelRect.bottom, GetColor(128, 128, 128), TRUE);

	int minute = floor(_remainTime / 60);
	
	int second = _remainTime % 60;

	/// !コロンが出ないのでカウントのみにする フォントアセット側の不具合？
	string remainTime = to_string(_remainTime);

	DrawStringToHandle(centerPos, 0, remainTime.c_str(), GetColor(255, 255, 255), fontHandle);

	/// アイテムの表示
	if (!itemPanelMap.empty())
	{
		TerrainList current = TerrainList::CUBE;
		while (true)
		{
			if (current == TerrainList::ItemAll) { break; }
			if (itemPanelMap[current] != nullptr)
			{
				auto it = itemPanelMap[current];
				it->Update();
			}
			current = (TerrainList)((int)current + 1);
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
	Draw(remainTime);
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

