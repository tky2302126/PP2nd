#include "AudioManager.h"

UniquePtr<AudioManager> AudioManager::Instance = nullptr;

AudioManager::AudioManager()
	:BGMVolume(0),SEVolume(0)
{
}

AudioManager::~AudioManager()
{
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
		Instance = make_unique<AudioManager>();
	}
	return *Instance;
}

void AudioManager::Load()
{
}

void AudioManager::Load(SceneName)
{
}

void AudioManager::LoadTest()
{
	BGMTrack[SETUP] = LoadSoundMem("./Resource/Sound/SetUp.mp3");
	BGMTrack[BATTLE1] = LoadSoundMem("./Resource/Sound/Battle1.mp3");
	BGMTrack[GAMEOVER] = LoadSoundMem("./Resource/Sound/GameOver.mp3");
	BGMTrack[GAMECLEAR] = LoadSoundMem("./Resource/Sound/lobby.mp3");
	SETrack[ALARM] = LoadSoundMem("./Resource/Sound/alarm.mp3");
	SETrack[ALERT] = LoadSoundMem("./Resource/Sound/alert.mp3");
	SETrack[LOWBON] = LoadSoundMem("./Resource/Sound/lowbon.mp3");
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

void AudioManager::SetLoop(bool)
{
}
