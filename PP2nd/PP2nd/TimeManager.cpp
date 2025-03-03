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
	// リザルト,デバッグ時は更新しない
	if (GM().CurrentSequence() == Result) return;
	if (GM().CurrentSequence() == Debug) return;

	if(remainTimeMS <=0)
	{
		if(CGM().CurrentSequence() == SetUp)
		{
			SetTimer(120);
			GM().SequenceProceed();
			AM().PlaySECustom(ALERT, BATTLE1);
		}
		else if(GM().CurrentSequence() == Battle)
		{
			GM().GameClear();
			return;
		}
	}
	int elapsedTime = deltaTime;
	if (isFast) { elapsedTime *= 2; }
	if (isSlow) { elapsedTime /= 2; }

	remainTimeMS -= elapsedTime;
	/// 敵の出現
	if (CGM().CurrentSequence() != Battle) return;
	if(!timeLine.empty())
	{
		while (!timeLine.empty()&&timeLine.top().Time >= remainTimeMS/1000)
		{
			auto tl = timeLine.top();
			timeLine.pop();
			/// ここに敵の出現 switch文
			/// 今はデバッグ対応

			EM().SpawnEnemy(tl.startPos,tl.enemy);
			if (timeLine.empty()) break;
		}
	}
}

void TimeManager::SetTimer(int _remainTime)
{
	remainTimeMS = _remainTime * 1000;
}

/// <summary>
/// エディット用のタイムライン読み込み
/// </summary>
void TimeManager::LoadTest()
{
	SetTimer(30);

	_timeLine.push_back({ 75,{0,9},{EnemyList::leela} });
	_timeLine.push_back({ 88,{0,9},{EnemyList::leela} });
	_timeLine.push_back({ 54,{0,9},{EnemyList::leela} });
	_timeLine.push_back({ 95,{0,9},{EnemyList::leela} });
	_timeLine.push_back({ 52,{0,9},{EnemyList::leela} });
	_timeLine.push_back({ 45,{0,9},{EnemyList::leela} });

	SetTimeLine(_timeLine);
}

TimeManager& TimeManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = std::make_unique<TimeManager>();
	}
	return *Instance;
}

void TimeManager::SetTimeLine(std::vector<TimeLine> _timeLine)
{
	for(const auto& tl :_timeLine)
	{
		timeLine.push(tl);
	}
}
