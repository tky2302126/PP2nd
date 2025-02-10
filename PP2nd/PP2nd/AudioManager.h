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
	void Load();
	void Load(SceneName);
	void Release(SEList);
	void Release(BGMList);
	void Release(SceneName);
	void PlayBGM();
	void PlaySE();
	void SetLoop(bool);
	void Init();
	void UnInit();

private:
	static UniquePtr<AudioManager> Instance;
	unmap<SEList, int> SETrack;
	unmap<BGMList, int> BGMTrack;
	bool loop = false;
};

