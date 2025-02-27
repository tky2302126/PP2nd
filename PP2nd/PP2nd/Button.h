#pragma once
#include "define.h"
#include "manager.h"
class Button
{
public:
	Button();
	~Button();
	void Init(RECTInt& _rect, int& _hoverColor, int& _normalColor, std::string& text);
	void Init(RECTInt& _rect, int& _hoverColor, int& _normalColor, std::string& text, std::function<void()> cb);
	void UnInit();
	void Update();
private:
	RECTInt rectInfo;
	int hoverColor;
	int normalColor;
	std::string buttonText;
	std::function<void()> cbFucntion; /// コールバック関数
};

