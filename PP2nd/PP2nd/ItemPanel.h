#pragma once
#include "define.h"

/// <summary>
/// HUD�ɕ\������A�C�e���p�l��
/// </summary>
class ItemPanel
{
public:
	void Init(int index,int& GH, int& num);
	void UnInit();
	void Update();
	void Decrease();
	void SetIndex(int index);
private:
	int GH;
	int num;
	bool selected;
	Vector2Int start;
	Vector2Int end;
};

