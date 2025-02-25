#pragma once
#include "SceneManager.h"
#include "InputSystem.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "TimeManager.h"
#include "AudioManager.h"

inline static GameManager& GM()
{
	return GameManager::GetInstance();
}

inline static const GameManager& CGM()
{
	return GameManager::GetInstance();
}

inline static EnemyManager& EM()
{
	return EnemyManager::GetInstance();
}

inline static const EnemyManager& CEM()
{
	return EnemyManager::GetInstance();
}

inline static AudioManager& AM()
{
	return AudioManager::GetInstance();
}

inline static const AudioManager& CAM()
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

inline static SceneManager& SM()
{
	return SceneManager::GetInstance();
}

inline static const SceneManager& CSM()
{
	return SceneManager::GetInstance();
}

inline static TimeManager& TM()
{
	return TimeManager::GetInstance();
}

inline static const TimeManager& CTM()
{
	return TimeManager::GetInstance();
}
