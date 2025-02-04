#pragma once
#include "define.h"

class TimeManager
{
public:
	void Init();
	void UnInit();
	void ChangeGameSpeedFaster(bool);
	void ChangeGameSpeedSlower(bool);
	void Update(int deltaTime);
	void SetTimer(int _remainTime);
	static TimeManager& GetInstance();
	
	int  RemainTime() const { return remainTime / 1000; }
	bool IsFast() const { return isFast; }
	bool IsSlow() const { return isSlow; }
private:
	bool isFast = false;
	bool isSlow = false;
	int remainTime = 0; /// メインループの制限時間ミリ秒単位で管理
	static UniquePtr<TimeManager> Instance;
};

