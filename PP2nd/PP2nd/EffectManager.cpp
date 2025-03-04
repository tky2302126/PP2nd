#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
}

void EffectManager::UnInit()
{
}

void EffectManager::Load(EffectList name)
{
	if (effectResource[name] >0) { return; }

	switch (name)
	{
	case Down:
		effectResource[name] = LoadEffekseerEffect("");
		break;
	case EffectAll:
		break;
	default:
		break;
	}
}

/// <summary>
/// エフェクトの再生指示
/// </summary>
/// <param name="name">エフェクトの種類</param>
/// <param name="pos">場所</param>
/// <param name="duration">時間</param>
void EffectManager::Play(EffectList name, VECTOR pos, float duration)
{
}

void EffectManager::Update()
{
}

void EffectManager::Draw()
{
}
