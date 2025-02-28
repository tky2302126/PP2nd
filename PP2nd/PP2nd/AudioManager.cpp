#include "AudioManager.h"

UniquePtr<AudioManager> AudioManager::Instance = nullptr;

AudioManager::AudioManager()
	:BGMVolume(0),SEVolume(0)
{
}

AudioManager::~AudioManager()
{
	if(asyncThread.joinable())
	{
		asyncThread.join();
	}
}

void AudioManager::Init()
{
	BGMVolume = 255 * BGM_VOLUME / 100;
	SEVolume = 255 * SE_VOLUME / 100;
}

void AudioManager::UnInit()
{
	for(int i=0;i<BGMList::BGM_ALL;i++)
	{
		auto it = BGMTrack.find((BGMList)i);
		// 見つからなかった場合
		if(it == BGMTrack.end() || it->second == -1)
		{
			continue;
		}
		int handle = it->second;
		auto result = DeleteSoundMem(handle);
		if (result == 0) { BGMTrack.erase(it); }
	}

	for (int i = 0; i < SEList::SE_ALL; i++)
	{
		// 見つからなかった場合
		if (SETrack.find((SEList)i) == SETrack.end())
		{
			continue;
		}
		DeleteSoundMem(SETrack[(SEList)i]);
	}
}

AudioManager& AudioManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = std::make_unique<AudioManager>();
	}
	return *Instance;
}

void AudioManager::Load()
{
}

void AudioManager::Load(SceneName name)
{
	switch (name)
	{
	case Title:
		if(BGMTrack[TITLE] <=0) BGMTrack[TITLE] = LoadSoundMem("./Resource/Sound/desert01.mp3");
		if (SETrack[LOWBON] <= 0)SETrack[LOWBON] = LoadSoundMem("./Resource/Sound/lowbon.mp3");
		break;
	case Menu:
		break;
	case Option:
		break;
	case Main:
		if (BGMTrack[SETUP] <= 0)BGMTrack[SETUP] = LoadSoundMem("./Resource/Sound/SetUp.mp3");
		if (BGMTrack[BATTLE1] <= 0)BGMTrack[BATTLE1] = LoadSoundMem("./Resource/Sound/Battle1.mp3");
		if (BGMTrack[GAMEOVER] <= 0)BGMTrack[GAMEOVER] = LoadSoundMem("./Resource/Sound/GameOver.mp3");
		if (BGMTrack[GAMECLEAR] <= 0)BGMTrack[GAMECLEAR] = LoadSoundMem("./Resource/Sound/lobby.mp3");
		if (SETrack[ALARM] <= 0)SETrack[ALARM] = LoadSoundMem("./Resource/Sound/alarm.mp3");
		if (SETrack[ALERT] <= 0)SETrack[ALERT] = LoadSoundMem("./Resource/Sound/alert.mp3");
		if (SETrack[LOWBON] <= 0)SETrack[LOWBON] = LoadSoundMem("./Resource/Sound/lowbon.mp3");
		break;
	case PreLoad:
		break;
	case Test:
		break;
	default:
		break;
	}
}

void AudioManager::LoadTest()
{
	if(BGMTrack[SETUP]<=0)BGMTrack[SETUP] = LoadSoundMem("./Resource/Sound/SetUp.mp3");
	if(BGMTrack[BATTLE1] <=0)BGMTrack[BATTLE1] = LoadSoundMem("./Resource/Sound/Battle1.mp3");
	if(BGMTrack[GAMEOVER] <=0)BGMTrack[GAMEOVER] = LoadSoundMem("./Resource/Sound/GameOver.mp3");
	if(BGMTrack[GAMECLEAR] <=0)BGMTrack[GAMECLEAR] = LoadSoundMem("./Resource/Sound/lobby.mp3");
	if(SETrack[ALARM] <=0)SETrack[ALARM] = LoadSoundMem("./Resource/Sound/alarm.mp3");
	if(SETrack[ALERT] <=0)SETrack[ALERT] = LoadSoundMem("./Resource/Sound/alert.mp3");
	if(SETrack[LOWBON] <=0)SETrack[LOWBON] = LoadSoundMem("./Resource/Sound/lowbon.mp3");
}

void AudioManager::Release(SEList)
{
}

void AudioManager::Release(BGMList)
{
}

void AudioManager::Release(SceneName)
{
}

void AudioManager::PlayBGM(BGMList name, bool loop)
{
	for (int i = 0; i < BGMList::BGM_ALL; i++)
	{
		auto it = BGMTrack.find((BGMList)i);
		// 見つからなかった場合
		if (it == BGMTrack.end() || it->second == -1)
		{
			continue;
		}
		int handle = it->second;
		auto result = StopSoundMem(handle);
	}

	if (BGMTrack.find(name) == BGMTrack.end()) { return; }
	ChangeVolumeSoundMem(BGMVolume, BGMTrack[name]);
	if(!loop)
	{
		PlaySoundMem(BGMTrack[name], DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundMem(BGMTrack[name], DX_PLAYTYPE_LOOP);
	}
}

void AudioManager::PlaySE(SEList name)
{
	PlaySoundMem(SETrack[name], DX_PLAYTYPE_BACK);
}

void AudioManager::PlaySECustom(SEList seName, BGMList bgmName, bool loop)
{
	for (int i = 0; i < BGMList::BGM_ALL; i++)
	{
		auto it = BGMTrack.find((BGMList)i);
		// 見つからなかった場合
		if (it == BGMTrack.end() || it->second == -1)
		{
			continue;
		}
		int handle = it->second;
		auto result = StopSoundMem(handle);
	}
	asyncThread = std::thread(&AudioManager::SurveySEAsync, this, seName);
	asyncThread.join();
	PlayBGM(bgmName, loop);
}

void AudioManager::SetLoop(bool)
{
}

void AudioManager::SurveySEAsync(SEList name)
{
	PlaySE(name);
	while (true)
	{
		if( CheckSoundMem(SETrack[name]) == 0)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	
}

void AudioManager::SurveySoundAsync(BGMList)
{
}
