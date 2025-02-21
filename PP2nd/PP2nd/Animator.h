#pragma once
#include "define.h"

enum AnimState
{
	Anim_Ready, // 再生待ち
	Anim_Start, // 再生開始
	Anim_Play,  // 再生中
	Blend_Start, // ブレンド開始
	BlendPlay   // ブレンド中
};

class Animator
{
public:
	Animator();
	~Animator();

	void Init(int MHandle);
	void UnInit();
	void Update();
	void Play(int id, float duration, bool loopFlg = false);
	bool IsPlay() { return isPlay; }
private:
	float playTime = -1;
	float totalTime = -1;
	float countDuration = 0;
	bool loop = false;
	int attachIndex1 = -1;
	int attachIndex2 = -1;
	float blendRate = -1;
	int mHandle;
	AnimState currentState;
	bool isPlay = false;
};

