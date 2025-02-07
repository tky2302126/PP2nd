#include "HUD.h"

HUD::HUD()
	:centerPos(0),fontHandle(-1),timerPanelRect(),playGH(-1),pauseGH(-1)
	,fastGH(-1),optionGH(-1),textHeight(0),textWidth(0),fast(false),skipGH(-1)
	,slowGH(-1)
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
	DeleteGraph(playGH);
	DeleteGraph(pauseGH);
	DeleteGraph(fastGH);
	DeleteGraph(optionGH);
	DeleteGraph(skipGH);
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
	const char* text = "000";
	GetDrawStringSizeToHandle(&textWidth, &textHeight, NULL, text, strlen(text), fontHandle);
	centerPos = (WINDOW_WIDTH - textWidth) / 2;
	timerPanelRect.left = centerPos;
	timerPanelRect.top = 0;
	timerPanelRect.right = centerPos + textWidth+5;
	timerPanelRect.bottom = textHeight;
	



	/// HUDパネルの準備
	playGH = LoadGraph("./Resource/play-button.png");
	pauseGH = LoadGraph("./Resource/pause-button.png");
	fastGH = LoadGraph("./Resource/fast-forward-button.png");
	slowGH = LoadGraph("./Resource/hourglass.png");
	optionGH = LoadGraph("./Resource/gears.png");
	skipGH = LoadGraph("./Resource/next-button.png");
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
	unordered_map<TerrainList, int> ItemInfoUnMap = GameManager::GetInstance().GetItemInfoUnMap();
	if (!ItemInfoUnMap.empty())
	{
		int index = 0;
		for (int i = 0; i < (int)TerrainList::ItemAll; i++)
		{
			auto it = ItemInfoUnMap.find((TerrainList)i);
			if (it != ItemInfoUnMap.end())
			{
				ItemPanel* itemPanelPtr = new ItemPanel();
				HDKey key = (HDKey)-1;
				switch ((TerrainList)i)
				{
				case TerrainList::CUBE:
					key = HDKey::Cube;
					break;
				default:

					break;
				}
				/// ここから変更
				/// 0になったとき 
				if(ItemInfoUnMap[(TerrainList)i] ==0)
				{
					delete itemPanelMap[(TerrainList)i];
					continue;
				}

				/// 追加
				if(itemPanelMap[(TerrainList)i] == nullptr)
				{
					int GH = GameManager::GetInstance().GetHandleData(key).GHandle;
					ItemInfo currentInfo;
					currentInfo.name = (TerrainList)i;
					currentInfo.num = ItemInfoUnMap[(TerrainList)i];
					itemPanelPtr->Init(index, GH, currentInfo, callback);
					index++;
					itemPanelMap[(TerrainList)i] = itemPanelPtr;
				}
				/// 更新
				else
				{
					/// 場所を更新
					itemPanelMap[(TerrainList)i]->SetIndex(index);
					/// 使用した場合
					if (itemPanelMap[(TerrainList)i]->GetNum() > ItemInfoUnMap[(TerrainList)i])
					{
						itemPanelMap[(TerrainList)i]->Decrease();
					}
				}
			}
		}
	}
}

/// <summary>
/// 未使用
/// </summary>
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
#pragma region 上部タイマー
	DrawBox(timerPanelRect.left, timerPanelRect.top, timerPanelRect.right, timerPanelRect.bottom, GetColor(64, 64, 64), TRUE);

	/// !コロンが出ないのでカウントのみにする フォントアセット側の不具合？
	string remainTime = to_string(_remainTime);
	if (_remainTime < 100) { remainTime = '0' + remainTime; }

	DrawStringToHandle(centerPos, 0, remainTime.c_str(), GetColor(255, 255, 255), fontHandle);
#pragma endregion

#pragma region 下部アイテムパネル
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
#pragma endregion



#pragma region 上部UI
	/// 設定ボタン(左上)
	DxLib::DrawExtendGraph(optionPos.left,optionPos.top,optionPos.right, optionPos.bottom,optionGH,FALSE);

	/// 再生速度ボタン
	if(TimeManager::GetInstance().IsSlow())
	{
		DxLib::DrawExtendGraph(playPos.left, playPos.top, playPos.right , playPos.bottom, slowGH, FALSE);
	}
	else if(TimeManager::GetInstance().IsFast())
	{
		DxLib::DrawExtendGraph(playPos.left, playPos.top, playPos.right, playPos.bottom, fastGH, FALSE);
	}
	else
	{
		DxLib::DrawExtendGraph(playPos.left, playPos.top, playPos.right, playPos.bottom, playGH, FALSE);
	}
	/// 一時停止、スキップボタン
	if(GameManager::GetInstance().CurrentSequence() == Sequence::Battle)
	{
		DxLib::DrawExtendGraph(skipPos.left, skipPos.top, skipPos.right, skipPos.bottom, pauseGH, FALSE);
	}
	else
	{
		DxLib::DrawExtendGraph(skipPos.left, skipPos.top, skipPos.right, skipPos.bottom, skipGH, FALSE);
	}


#pragma endregion

}

/// <summary>
/// 未使用
/// </summary>
void HUD::Update()
{
	Draw();
	if (GameManager::GetInstance().ItemInfoChanged()) 
	{
		ReLoad();
		GameManager::GetInstance().CheckedItemInfo();
	}
}
/// <summary>
/// 時間の更新を実行するUpdate
/// </summary>
/// <param name="remainTime"></param>
void HUD::Update(int remainTime)
{
	Draw(remainTime);
	if (GameManager::GetInstance().ItemInfoChanged())
	{
		ReLoad();
		GameManager::GetInstance().CheckedItemInfo();
	}

#pragma region 入力
	auto mouseInfo = InputSystem::GetInstance().GetMouseInfo();
	if (mouseInfo.state.left != Started) return;
	/// オプション 
	if(CheckInRect(mouseInfo.position, optionPos))
	{
		/// オプションウィンドウを表示
	}
	/// 再生ボタン
	if(CheckInRect(mouseInfo.position, playPos))
	{
		/// 再生速度の変更
		if(TimeManager::GetInstance().IsFast())
		{
			TimeManager::GetInstance().ChangeGameSpeedFaster(false);
		}
		else
		{
			TimeManager::GetInstance().ChangeGameSpeedFaster(true);
		}
	}
	/// 一時停止ボタン
	if(CheckInRect(mouseInfo.position, skipPos))
	{
		/// シーケンスで分岐
		/// スキップボタン->シーケンスをスキップ
		if(GameManager::GetInstance().CurrentSequence() == SetUp)
		{
			TimeManager::GetInstance().SetTimer(0);
		}
		/// 停止ボタン->ゲーム内時間を一時停止
		else if(GameManager::GetInstance().CurrentSequence() == Battle)
		{
			TimeManager::GetInstance().Pause();
		}
	}
#pragma endregion

}


