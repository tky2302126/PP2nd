#include "EffectManager.h"

UniquePtr<EffectManager> EffectManager::Instance = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

EffectManager& EffectManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = std::make_unique<EffectManager>();
	}
	return *Instance;
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
		effectResource[name] = LoadEffekseerEffect("./Resource/down.efk");
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
	Effekseer_Sync3DSetting();

	UpdateEffekseer3D();

}

void EffectManager::Draw()
{
	DrawEffekseer3D();
}

void EffectManager::SurveyHandle()
{

}
