#pragma once
#include "define.h"
#include "Item.h"
/// <summary>
/// マップに設置する障害物
/// </summary>
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

