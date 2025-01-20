#pragma once
#include "define.h"
#include "manager.h"

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
	void Init();
	void UnInit();

	void Load();
	void Draw();
	void Update();
	void Update(int remainTime);
	void RegistItem(int gHandle);
	void ExcludeItem(int gHandle);
	void UseItem();


private:
	int x;
	int fontHandle;
	int textWidth;
	int	textHeight;
	int rectLeft;
	int rectTop;
	int rectRight;
	int rectBottom;
	int padding = 0;
	int oldRemainTime;




};

