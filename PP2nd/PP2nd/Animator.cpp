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
}

Animator::~Animator()
{
}

void Animator::Init(int MHandle)
{
	mHandle = MHandle;
}

void Animator::UnInit()
{
}

void Animator::Update()
{
	
	/// 再生の終了
	if(playTime >= totalTime)
	{
		if(loop)
		{
			playTime = 0;
			currentState = Anim_Start;
		}
		else
		{
			attachIndex1 = -1;
			currentState = Anim_Ready;
			isPlay = false;
		}
	}

	/// ブレンドの終了
	if(blendRate >= 1.0)
	{
		attachIndex1 = attachIndex2;
		totalTime = MV1GetAttachAnimTotalTime(mHandle, attachIndex1);
		currentState = Anim_Start;
		blendRate = -1;
	}

	switch (currentState)
	{
	case Anim_Start:
		MV1SetAttachAnimTime(mHandle, attachIndex1, playTime);
		currentState = Anim_Play;
		break;
	case Anim_Play:
		playTime += countDuration;
		MV1SetAttachAnimTime(mHandle, attachIndex1, playTime);
		break;
	case Blend_Start:
		blendRate = 0;
		MV1SetAttachAnimBlendRate(mHandle, attachIndex1, 1.0);
		MV1SetAttachAnimBlendRate(mHandle, attachIndex2, 0);
		currentState = BlendPlay;
		break;
	case BlendPlay:
		blendRate += ANIMATION_BLEND_RATE;
		MV1SetAttachAnimBlendRate(mHandle, attachIndex1, 1.0-blendRate);
		MV1SetAttachAnimBlendRate(mHandle, attachIndex2, blendRate);
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
void Animator::Play(int id, float duration, bool loopFlg)
{	/// 再生
	if(currentState == Anim_Ready)
	{
		attachIndex1 = MV1AttachAnim(mHandle, id);
		totalTime = MV1GetAttachAnimTotalTime(mHandle, attachIndex1);
		playTime = 0;
		countDuration = totalTime / (duration * FRAMERATE);
		currentState = Anim_Start;
		loop = loopFlg;
		isPlay = true;
	}

	/// ブレンド
	if(currentState == Anim_Play)
	{
		attachIndex2 = MV1AttachAnim(mHandle, id);
		playTime = 0;
		float tmpTotalTime = MV1GetAttachAnimTotalTime(mHandle, attachIndex2);
		countDuration = tmpTotalTime / (duration * FRAMERATE);
		loop = loopFlg;
		currentState = Blend_Start;
	}
}
