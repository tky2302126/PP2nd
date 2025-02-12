#include "TimeManager.h"
#include "manager.h"


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
	isSlow = false; 
}

void TimeManager::ChangeGameSpeedSlower(bool _isSlow)
{
	isSlow = _isSlow;
	isFast = false; 
}

void TimeManager::Pause()
{
	isPause = true;
}

void TimeManager::UnPause()
{
	isPause = false;
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void TimeManager::Update(int deltaTime)
{
	// リザルト時は更新しない
	if (GameManager::GetInstance().CurrentSequence() == Result) return;

	if(remainTime <=0)
	{
		if(GameManager::GetInstance().CurrentSequence() == SetUp)
		{
			SetTimer(100);
			GameManager::GetInstance().SequenceProceed();
			AudioManager::GetInstance().PlaySECustom(ALERT, BATTLE1);
			// AudioManager::GetInstance().PlaySE(SEList::ALERT);
			// AudioManager::GetInstance().PlayBGM(BGMList::BATTLE1);
		}
		else if(GameManager::GetInstance().CurrentSequence() == Battle)
		{
			GameManager::GetInstance().GameClear();
			return;
		}
	}
	int elapsedTime = deltaTime;
	if (isFast) { elapsedTime *= 2; }
	if (isSlow) { elapsedTime /= 2; }

	remainTime -= elapsedTime;
	/// 敵の出現
	if (GameManager::GetInstance().CurrentSequence() != Battle) return;
	if(!timeLine.empty())
	{
		while (timeLine.top().Time >= remainTime/1000)
		{
			auto tl = timeLine.top();
			timeLine.pop();
			/// ここに敵の出現 switch文
			/// 今はデバッグ対応

			EnemyManager::GetInstance().SpawnEnemyTest();
			if (timeLine.empty()) break;
		}
	}
}

void TimeManager::SetTimer(int _remainTime)
{
	remainTime = _remainTime * 1000;
}

void TimeManager::LoadTest()
{
	SetTimer(30);
	timeLine.push({ 75,{0,0},{EnemyList::Enemy1},99 });
	timeLine.push({ 88,{0,0},{EnemyList::Enemy1},99 });
	timeLine.push({ 54,{0,0},{EnemyList::Enemy1},99 });
	timeLine.push({ 95,{0,0},{EnemyList::Enemy1},99 });
}

TimeManager& TimeManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = make_unique<TimeManager>();
	}
	return *Instance;
}
