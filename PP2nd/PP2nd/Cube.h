#pragma once
#include "define.h"
#include "Item.h"
class Cube :public Item
{
public:
	Cube();
	~Cube();

	void Init();
	void UnInit();

	void OnEnter();
	void OnExit();

	int& GetGHandle();
	int& GetMHandle();
private:
	int GHandle;
};

