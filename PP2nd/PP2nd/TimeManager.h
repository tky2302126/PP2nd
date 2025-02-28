#pragma once
#include "define.h"

class TimeManager
{
public:
	void Init();
	void UnInit();
	void ChangeGameSpeedFaster(bool);
	void ChangeGameSpeedSlower(bool);
	void Pause();
	void UnPause();
	void Update(int deltaTime);
	void SetTimer(int _remainTime);
	void LoadTest();
	static TimeManager& GetInstance();
	
	int  RemainTime() const { return remainTime / 1000; }
	bool IsFast() const { return isFast; }
	bool IsSlow() const { return isSlow; }
	bool IsPause() const { return isPause; }
	std::vector<TimeLine> GetTimeLine() {return _timeLine;}
	void SetTimeLine(std::vector<TimeLine> _timeLine);
private:
	bool isFast = false;
	bool isSlow = false;
	bool isPause = false;
	int remainTime = 0; /// メインループの制限時間ミリ秒単位で管理
	std::priority_queue<TimeLine, std::vector<TimeLine>, TimeLineCompare> timeLine;
	std::vector<TimeLine> _timeLine; /// エディット用に使う配列
	static UniquePtr<TimeManager> Instance;
};

