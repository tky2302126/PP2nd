#pragma once
#include "DxLib.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>
#include <thread>

using namespace std;


constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

constexpr int FRAMERATE = 60;  //ゲーム全体のフレームレート
constexpr auto FRAME_TIME_MS = 1000 / FRAMERATE;
constexpr auto MAP_UNIT = 200.0f;  //マップの1ユニットの長さ

constexpr float CAMERA_HEIGHT = 1800.0f;

const auto COLOR_AMBER = GetColorU8(185, 126, 84, 255);
const auto COLOR_WHITE = GetColorU8(255, 255, 255, 255);
const auto COLOR_NONE = GetColorU8(0, 0, 0, 0);

enum SceneName
{
	Title,
	Menu,
	Option,
	Main,
	PreLoad,
	Test,
	ALL
};

typedef struct
{
	int x ;
	int y ;
}Vector2Int;

#pragma region InputSystem 
enum InputState
{
	None,
	Started,
	Performed,
	Canceled
};

struct _mouseState
{
	InputState left = None;
	InputState right = None;
}typedef MouseState;

typedef struct MouseInfo
{
	Vector2Int position;
	MouseState state;
};
#pragma endregion


