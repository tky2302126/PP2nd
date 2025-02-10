#include "AudioManager.h"

UniquePtr<AudioManager> AudioManager::Instance = nullptr;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
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

void AudioManager::Init()
{
}

void AudioManager::UnInit()
{
}
