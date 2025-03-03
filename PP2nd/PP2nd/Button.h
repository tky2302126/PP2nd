#pragma once
#include "define.h"
#include "manager.h"
class Button
{
public:
	Button();
	~Button();
	void Init(const RECTInt& _rect, const int& _hoverColor, const int& _normalColor, const std::string& text, const std::function<void()> cb);
	void Update();
private:
	RECTInt rectInfo;
	int hoverColor;
	int normalColor;
	std::string buttonText;
	std::function<void()> cbFunction; /// コールバック関数
};

