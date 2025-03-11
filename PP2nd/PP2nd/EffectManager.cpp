#include "EffectManager.h"

UniquePtr<EffectManager> EffectManager::Instance = nullptr;

EffectManager::EffectManager()
{
	Init();
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
	graphHandle = LoadGraph("./Resource/Background.png");
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void EffectManager::UnInit()
{
	DeleteGraph(graphHandle);

	for(auto& [key, effectResource] : effectResource)
	{
		DeleteEffekseerEffect(effectResource);
	}
	effectResource.clear();
}

void EffectManager::Load(EffectList name)
{
	if (effectResource[name] >0) { return; }
 	switch (name)
	{
	case Down:
		effectResource[name] = LoadEffekseerEffect(_T("./Resource/Effect/hit_hanmado_0409.efkefc"),30);
		break;
	case Magma:
		
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
	DrawGraph(-2000, -2000, graphHandle, true);

	SurveyHandle();

	// Effekseer_Sync3DSetting();

	UpdateEffekseer3D();

	Draw();

#if _DEBUG
	// clsDx();
	// 
	// printfDx("再生中のエフェクト: %d", playingEffectHandle.size());
#endif
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
