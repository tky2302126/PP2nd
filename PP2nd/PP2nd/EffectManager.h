#pragma once
#include "define.h"
#include "Effect.h"
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	static EffectManager& GetInstance();
	void Init();
	void UnInit();
	void Load(EffectList name);
	void Play(EffectList name, VECTOR pos, float duration);
	void Update();
	void Draw();

private:
	void SurveyHandle();

private:
	unmap<EffectList, int> effectResource;
	static UniquePtr<EffectManager> Instance;
	std::vector<int> effectHandle;
};

