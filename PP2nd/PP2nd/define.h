#pragma once
#include "DxLib.h"
#include "MyMath.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <filesystem>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;
namespace fs = std::filesystem;

template <typename T1,typename T2>
using unmap = unordered_map<T1,T2>;

template <typename T>
using SharedPtr = shared_ptr<T>;

template <typename T>
using UniquePtr = unique_ptr<T>;

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

constexpr int FRAMERATE = 60;  //ゲーム全体のフレームレート
constexpr auto FRAME_TIME_MS = 1000 / FRAMERATE;
constexpr auto MAP_UNIT = 360.0f;  //マップの1ユニットの長さ


constexpr float CAMERA_HEIGHT = 3000.0f;
constexpr float CAMERA_Z_OFFSET = -1000.0f;
constexpr auto MAP_MARGIN = 0.1f ; //マップの余白
constexpr float MAP_HEIGHT = 3600.0f; //正射影カメラの縦の幅(マップの縦の長さ)
constexpr float MAP_WIDTH = MAP_HEIGHT / 9 * 16;

constexpr auto CAMERA_MIN_Z = MAP_HEIGHT / 2;
constexpr auto CAMERA_MIN_X = CAMERA_MIN_Z / 9 * 16;

constexpr auto HUD_ITEM_SIZE = WINDOW_WIDTH / 10;

constexpr auto HUD_AREA_TOP = 50;
constexpr auto HUD_AREA_BOTTOM = WINDOW_HEIGHT- HUD_ITEM_SIZE;
constexpr auto ITEMPANEL_SELECTED = HUD_ITEM_SIZE / 5;

const auto COLOR_AMBER = GetColorU8(185, 126, 84, 255);
const auto COLOR_WHITE = GetColorU8(255, 255, 255, 255);
const auto COLOR_NONE = GetColorU8(0, 0, 0, 0);
const auto COLOR_PURPLE = GetColorU8(255, 0, 255, 0); /// 透過用の色
const auto COLOR_LIGHTBLUE = GetColorU8(88, 231, 248, 255); /// 透過用の色

enum SceneName
{
	Title,
	Menu,
	Option,
	Main,
	PreLoad,
	Test,
};

struct Vector2Int
{
	int x ;
	int y ;
};

/// <summary>
/// 矩形を描画するための構造体
/// </summary>
struct RECTInt
{
	int top;
	int bottom;
	int left;
	int right;
};

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

struct MouseInfo
{
	Vector2Int position;
	MouseState state;

	MouseInfo() = default;
};
#pragma endregion


#pragma region Map
enum class TerrainList
{
	None = -1,
	Item1,

	Invailed =66, // 配置不可
	Polluted =99, // 汚染エリア
};

struct _mapInfo
{
	int width;
	int height;
	int goalWidth;
	int goalHeight;

	_mapInfo() = default;

	_mapInfo(int _width, int _height, int _goalWidth, int _goalHeight)
		:width(_width), height(_height), goalWidth(_goalWidth), goalHeight(_goalHeight) {}
};
#pragma endregion

enum class Tag :int
{
	Start,
	Goal
};

///
inline string GetExecutablePath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH); //絶対パスを取得
	string path(buffer);
	return path.substr(0,path.find_last_of("\\/")); //ディレクトリ部分を抽出
}

#pragma region GameManager
struct HandleData
{
	int GHandle;
	int MHandle;
};

enum ItemList
{
	Cube,
	ALL
};

struct ItemInfo
{
	ItemList name;
	int num;
};

enum class HDKey 
{
	Play,
	Pause,
	Fast_Forward,
	Cube =99,
	Item2,
	Item3,
	Enemy1=999,
	Enemy2,
};

#pragma endregion

