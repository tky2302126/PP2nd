#pragma once
#include "define.h"
#include "Effect.h"
class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	void Init();
	void UnInit();
	void Load(EffectList name);
	void Play(EffectList name, VECTOR pos, float duration);
	void Update();
	void Draw();

private:
	unmap<EffectList, int> effectResource;
};

