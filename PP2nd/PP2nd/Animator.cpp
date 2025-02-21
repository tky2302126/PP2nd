#include "Animator.h"

/// <summary>
/// アニメーション制御
/// Playで再生
/// 再生中のアニメーションがあった場合、ブレンド
/// 無いとき、普通に再生
/// </summary>

Animator::Animator()
{
	currentState = Anim_Ready;
	mHandlePtr = nullptr;
}

Animator::~Animator()
{
}

void Animator::Init(int MHandle)
{
	mHandlePtr = &MHandle;
}

void Animator::UnInit()
{
}

void Animator::Update()
{
	if (mHandlePtr == nullptr) { return; }
	switch (currentState)
	{
	case Anim_Start:
		break;
	case AnimState::Anim_Play:
		break;
	case BlendStart:
		break;
	case BlendPlay:
		break;
	default:
		break;
	}
}

/// <summary>
/// 再生指示
/// </summary>
/// <param name="id">再生するクリップ</param>
/// <param name="duration">再生時間</param>
/// <param name="loopFlg">ループフラグ</param>
void Animator::Play(int id, float duration, bool loopFlg = false)
{
	if(currentState == Anim_Ready || currentState == Anim_Play)
	{
		totalTime = MV1GetAttachAnimTotalTime(*mHandlePtr, id);

	}
}
