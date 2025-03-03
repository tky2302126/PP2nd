#include "Button.h"

Button::Button()
	:hoverColor(-1),normalColor(0),cbFunction(nullptr)
{
}

Button::~Button()
{
}

void Button::Init(const RECTInt& _rect, const int& _hoverColor, const int& _normalColor, const std::string& text, const std::function<void()> cb)
{
	rectInfo = _rect;
	hoverColor = _hoverColor;
	normalColor = _normalColor;
	buttonText = text;
	cbFunction = cb;
}

void Button::Update()
{
	/// 入力
	auto mouseInfo = Input().GetMouseInfo();
	/// 描画
	/// ホバー
	if(CheckInRect(mouseInfo.position, rectInfo))
	{
		DrawBox(rectInfo.left, rectInfo.top, rectInfo.right, rectInfo.bottom, hoverColor, TRUE);
		DrawFormatString(rectInfo.left, rectInfo.top, GetColor(255, 255, 255), buttonText.c_str());

		/// クリック
		if(mouseInfo.state.left == Canceled)
		{
			if(cbFunction)
			{
				cbFunction();
			}
		}
	}
	else
	{
		DrawBox(rectInfo.left, rectInfo.top, rectInfo.right, rectInfo.bottom, normalColor, TRUE);
		DrawFormatString(rectInfo.left, rectInfo.top, GetColor(255, 255, 255), buttonText.c_str());
	}
}
