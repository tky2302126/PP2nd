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
		effectResource[name] = LoadEffekseerEffect("./Resource/down.efk",100);
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
	auto playEffect = PlayEffekseer3DEffect(effectResource[name]);
	auto result = SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);
	playingEffectHandle.push_back(playEffect);
}

void EffectManager::Update()
{
	clsDx();

	SurveyHandle();

	Effekseer_Sync3DSetting();

	UpdateEffekseer3D();

	Draw();

	printfDx("再生中のエフェクト: %d", playingEffectHandle.size());
}

void EffectManager::Draw()
{
	DrawEffekseer3D();
}

/// <summary>
/// エフェクトはワンショット想定なので、再生が終了したら削除する
/// </summary>
void EffectManager::SurveyHandle()
{
	for(auto it = playingEffectHandle.begin(); it != playingEffectHandle.end();)
	{
		if(IsEffekseer3DEffectPlaying(*it) == -1)
		{
			it = playingEffectHandle.erase(it);
		}
		else
		{
			it++;
		}
	}
}
