#pragma once
#include "define.h"

/// <summary>
/// �}�b�v�ɕ`�悷��A�C�e���̃N���X
/// </summary>
class Box
{
public:
	void Init();
	void Init(const VECTOR& pos,const Tag& tag);
	void UnInit();
	void Draw();
private:
	VERTEX3D Vertex[8];
	WORD Index[36];
	VECTOR pos;
	Tag tag;
	int lineColor;
};

