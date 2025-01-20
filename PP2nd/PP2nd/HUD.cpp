#include "HUD.h"

HUD::HUD()
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
	x = (WINDOW_WIDTH - textWidth) / 2;
	rectLeft = x - padding;
	rectTop = 0;
	rectRight = x + textWidth + padding;
	rectBottom = textHeight + padding;
}

void HUD::UnInit()
{

}

void HUD::Load()
{

}

void HUD::Draw()
{
	DrawBox(rectLeft, rectTop, rectRight, rectBottom, GetColor(128, 128, 128), TRUE);

	DrawStringToHandle(x, 0, "00:00", GetColor(255, 255, 255), fontHandle);
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
