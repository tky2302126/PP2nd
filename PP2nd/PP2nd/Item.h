#pragma once
#include"define.h"

/// <summary>
/// İ’u•¨‚ÌŠî’êƒNƒ‰ƒX
/// </summary>

class Item
{
public:
	virtual void Init(int) = 0;
	virtual void Init(int,VECTOR) = 0;
	virtual ~Item() = default;
	virtual void OnEnter() const =0;
	virtual void OnExit() const =0;
	virtual void Draw() const = 0;
	virtual void Update() const = 0;
	virtual void Confirm() const = 0;
	virtual int& GetMHandle() const = 0;

};


