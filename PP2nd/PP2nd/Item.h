#pragma once
#include"define.h"

/// <summary>
/// �ݒu���̊��N���X
/// </summary>

class Item
{
public:
	virtual ~Item() = default;
	virtual void OnEnter() const =0;
	virtual void OnExit() const =0;

	// virtual int& GetGHandle() const = 0;
	virtual int& GetMHandle() const = 0;

};


