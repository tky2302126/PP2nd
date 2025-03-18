#pragma once
#include "define.h"
#include "manager.h"
#include "ItemPanel.h"

/// <summary>
/// HUD制御のクラス
/// !todo
/// 画面右上部分にゲームスピード変更UIの実装
/// 画面下部にアイテムパネルを実装
/// </summary>
class HUD
{
public:
	HUD();
	~HUD();
	void Init(SceneName name = Main);
	void SetCallback(std::function<void(TerrainList)>);
	void UnInit();

	void Load();
	void ReLoad();
	void Draw();
	void Draw(int);
	void Update();
	void Update(int remainTime);


private:
#pragma region 上部タイマー
	int centerPos;
	int fontHandle;
	int textWidth;
	int	textHeight;
	RECTInt timerPanelRect;
#pragma endregion
#pragma region 残敵数

#pragma endregion
#pragma region 準備フェイズ表示UI

	const int maxCount =30;
	RECTInt standbyGauge = 
	{
		60,
		120,
		170,
		WINDOW_WIDTH-170
	};
#pragma endregion



	bool fast;
	int playGH;
	int pauseGH;
	int fastGH;
	int slowGH;
	int optionGH;
	int skipGH;
	RECTInt optionPos =
	{
		HUD_UI_MARGIN,
		HUD_UI_MARGIN + HUD_UI_SIZE,
		HUD_UI_MARGIN,
		HUD_UI_MARGIN + HUD_UI_SIZE
	};
	RECTInt playPos = 
	{
		HUD_UI_MARGIN,
		HUD_UI_MARGIN + HUD_UI_SIZE,
		WINDOW_WIDTH - (HUD_UI_SIZE + HUD_UI_MARGIN) * 2,
		WINDOW_WIDTH - HUD_UI_SIZE - HUD_UI_MARGIN * 2
	};
	RECTInt skipPos =
	{
		HUD_UI_MARGIN,
		HUD_UI_MARGIN + HUD_UI_SIZE,
		WINDOW_WIDTH - HUD_UI_SIZE - HUD_UI_MARGIN,
		WINDOW_WIDTH - HUD_UI_MARGIN
	};

	unmap<TerrainList, ItemPanel*> itemPanelMap;
	std::function<void(TerrainList)> callback; //アイテムパネルクラスに登録する用のコールバック関数
};

