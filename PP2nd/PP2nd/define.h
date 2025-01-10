#pragma once
#include "DxLib.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;


constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

constexpr auto FRAMERATE = 60.0f;  //ゲーム全体のフレームレート
constexpr auto MAP_UNIT = 200.0f;  //マップの1ユニットの長さ

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
	int x;
	int y;
}Vector2Int;

