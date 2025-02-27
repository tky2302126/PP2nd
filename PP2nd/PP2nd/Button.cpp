#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(RECTInt& _rect, int& _hoverColor, int& _normalColor, std::string& text)
{
	rectInfo = _rect;
	hoverColor = _hoverColor;
	normalColor = _normalColor;
	buttonText = text;
}

void Button::Init(RECTInt& _rect, int& _hoverColor, int& _normalColor, std::string& text, std::function<void()> cb)
{
	rectInfo = _rect;
	hoverColor = _hoverColor;
	normalColor = _normalColor;
	buttonText = text;
	cbFucntion = cb;
}

void Button::UnInit()
{
}

void Button::Update()
{
	/// 入力
	auto mouseInfo = Input().GetMouseInfo();
	/// ホバー
	if(CheckInRect(mouseInfo.position, rectInfo))
	{
		DrawBox(rectInfo.left, rectInfo.top, rectInfo.right, rectInfo.bottom, hoverColor, TRUE);
		DrawFormatString(rectInfo.left, rectInfo.top, GetColor(255, 255, 255), buttonText.c_str());

		/// クリック
		if(mouseInfo.state.left == Canceled)
		{
			if(cbFucntion)
			{
				cbFucntion();
			}
		}
	}
	else
	{
		DrawBox(rectInfo.left, rectInfo.top, rectInfo.right, rectInfo.bottom, normalColor, TRUE);
		DrawFormatString(rectInfo.left, rectInfo.top, GetColor(255, 255, 255), buttonText.c_str());
	}

	/// 描画
	
}
