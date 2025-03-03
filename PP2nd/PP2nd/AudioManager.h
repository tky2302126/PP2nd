#pragma once
#include"define.h"

/// <summary>
/// BGM,SEを管理
/// 動的メモリに確保するBGMは50ｍｂ程度を目指す
/// 現状80ｍｂ程度なのであまり気にしなくてよい？
/// 読み込みタイミングのみ注意する
/// </summary>
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	static AudioManager& GetInstance();
	void Init();
	void UnInit();
	void Load();
	void Load(SceneName);
	void LoadTest();
	void Release(SEList);
	void Release(BGMList);
	void Release(SceneName);
	void PlayBGM(BGMList name, bool loop = true);
	void PlaySE(SEList);
	void PlaySECustom(SEList, BGMList, bool loop = true);
	void SetLoop(bool);

private:
	static UniquePtr<AudioManager> Instance;
	unmap<SEList, int> SETrack;
	unmap<BGMList, int> BGMTrack;
	bool loop = false;
	int BGMVolume;
	int SEVolume;
	int surveyHandle = -1;
	int surveyConunt = -1;
	int oldVolume = -1;
	std::thread asyncThread;
	std::mutex seMutex;
	void SurveySEAsync(SEList);
};

