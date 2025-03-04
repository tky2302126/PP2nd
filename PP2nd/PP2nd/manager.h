#pragma once
#include "SceneManager.h"
#include "InputSystem.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "TimeManager.h"
#include "AudioManager.h"
#include "EffectManager.h"

inline static GameManager& GameM()
{
	return GameManager::GetInstance();
}

inline static const GameManager& CGameM()
{
	return GameManager::GetInstance();
}

inline static EnemyManager& EnemyM()
{
	return EnemyManager::GetInstance();
}

inline static const EnemyManager& CEnemyM()
{
	return EnemyManager::GetInstance();
}

inline static AudioManager& AudioM()
{
	return AudioManager::GetInstance();
}

inline static const AudioManager& CAudioM()
{
	return AudioManager::GetInstance();
}

inline static InputSystem& Input()
{
	return InputSystem::GetInstance();
}

inline static const InputSystem& CInput()
{
	return InputSystem::GetInstance();
}

inline static SceneManager& SceneM()
{
	return SceneManager::GetInstance();
}

inline static const SceneManager& CSceneM()
{
	return SceneManager::GetInstance();
}

inline static TimeManager& TimeM()
{
	return TimeManager::GetInstance();
}

inline static const TimeManager& CTimeM()
{
	return TimeManager::GetInstance();
}

inline static EffectManager& EffectM()
{
	return EffectManager::GetInstance();
}

inline static const EffectManager& CEffectM()
{
	return EffectManager::GetInstance();
}
