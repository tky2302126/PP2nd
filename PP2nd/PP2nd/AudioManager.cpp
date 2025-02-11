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
	BGMTrack[GAMECLEAR] = LoadSoundMem("./Resource/Sound/lobby.mp3");
	BGMTrack[GAMEOVER] = LoadSoundMem("./Resource/Sound/GameOver.mp3");
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

void AudioManager::PlayBGM()
{
}

void AudioManager::PlaySE()
{
}

void AudioManager::SetLoop(bool)
{
}
