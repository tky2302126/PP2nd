#include "TimeManager.h"

UniquePtr<TimeManager> TimeManager::Instance = nullptr;

void TimeManager::Init()
{
	isFast = false;
	isSlow = false;
}

void TimeManager::UnInit()
{
}

void TimeManager::ChangeGameSpeedFaster(bool _isFast)
{
	isFast = _isFast;
	if (isFast) { isSlow = false; }
}

void TimeManager::ChangeGameSpeedSlower(bool _isSlow)
{
	isSlow = _isSlow;
	if (isSlow) { isFast = false; }
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void TimeManager::Update(int deltaTime)
{
	int elapsedTime = deltaTime;
	if (isFast) { elapsedTime *= 2; }
	if (isSlow) { elapsedTime /= 2; }

	remainTime -= elapsedTime;
}

void TimeManager::SetTimer(int _remainTime)
{
	remainTime = _remainTime * 1000;
}

TimeManager& TimeManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = make_unique<TimeManager>();
	}
	return *Instance;
}
