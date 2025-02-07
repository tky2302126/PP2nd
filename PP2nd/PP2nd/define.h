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
#include <functional>
#include <cmath>
#include <unordered_set>

using namespace std;
namespace fs = std::filesystem;

template<typename T1,typename T2,typename T3 = hash<T1>>
using unmap = unordered_map<T1, T2, T3>;

template <typename T>
using SharedPtr = shared_ptr<T>;

template <typename T>
using UniquePtr = unique_ptr<T>;

using Clock = chrono::high_resolution_clock;

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

constexpr int FRAMERATE = 60;  //ゲーム全体のフレームレート
constexpr auto FRAME_TIME_MS = 1000 / FRAMERATE;
constexpr auto MAP_UNIT = 360.0f;  //マップの1ユニットの長さ


constexpr float CAMERA_HEIGHT = 2000.0f;
constexpr float CAMERA_Z_OFFSET = CAMERA_HEIGHT/2; // 60度の仰角
constexpr auto MAP_MARGIN = 0.1f ; //マップの余白(割合)
constexpr auto CAMERA_VROTATE = 60.0f;

constexpr auto CAMERA_MIN_Z = CAMERA_HEIGHT / 2;
constexpr auto CAMERA_MIN_X = CAMERA_MIN_Z / 9 * 16;

constexpr auto HUD_ITEM_SIZE = WINDOW_WIDTH / 10;
constexpr auto HUD_UI_SIZE = WINDOW_WIDTH / 20;
constexpr auto HUD_UI_MARGIN = 20;

constexpr auto HUD_AREA_TOP = 50;
constexpr auto HUD_AREA_BOTTOM = WINDOW_HEIGHT- HUD_ITEM_SIZE;
constexpr auto ITEMPANEL_SELECTED = HUD_ITEM_SIZE / 5;

constexpr auto CONFIRM_PANEL_OFFSET = 25;
constexpr auto CONFIRM_PANEL_SIZE = 40;

constexpr auto ENEMY_MOVE_SPEED = 6.0f;
constexpr auto ENEMY_GAUGE_WIDTH = 50;
constexpr auto ENEMY_GAUGE_HEIGHT = 10;
constexpr auto ENEMY_GAUGE_OFFSET_Y = 25;

constexpr auto GAMESPEED_SLOWRATE = 0.5f;
constexpr auto GAMESPEED_FASTRATE = 2.0f;

const auto COLOR_AMBER = GetColorU8(185, 126, 84, 255);
const auto COLOR_WHITE = GetColorU8(255, 255, 255, 255);
const auto COLOR_NONE = GetColorU8(0, 0, 0, 0);
const auto COLOR_PURPLE = GetColorU8(255, 0, 255, 0); /// 透過用の色
const auto COLOR_LIGHTBLUE = GetColorU8(88, 231, 248, 255); /// ゴールの色
const auto COLOR_RED = GetColorU8(255, 0, 0, 255); /// スタートの色

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

	bool operator== (const Vector2Int& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Vector2Int& other) const { return !(*this == other); }
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
	Goal=0,
	Base,
	None,
	CUBE,
	ItemAll,

	Invailed =666, // 配置不可
	Polluted =999, // 汚染エリア
	Start,
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

enum EnemyList
{
	Enemy1,
	ALL
};

/// <summary>
/// 敵の出現パターンを定義する構造体
/// </summary>
struct TimeLine
{
	int Time;
	Vector2Int startPos;
	EnemyList enemy;
	int num;
};
/// <summary>
/// TimeLineソート用の比較関数
/// </summary>
struct TimeLineCompare
{
	bool operator()(const TimeLine& a, const TimeLine& b)
	{
		return a.Time < b.Time;
	}
};

#pragma region GameManager
struct HandleData
{
	int GHandle;
	int MHandle;
};

struct ItemInfo
{
	TerrainList name;
	int num;
};

enum class HDKey 
{
	Play,
	Pause,
	Fast_Forward,
	Check,
	Cross,
	Cube =0,
	Item2,
	Item3,
	Enemy1=999,
	Enemy2,
};

enum Sequence
{
	SetUp,
	Battle,
	Result
};

#pragma endregion

#pragma region 経路探索
/// <summary>
/// 経路探索用のノード
/// </summary>
struct Node
{
	Vector2Int pos;
	int cost;
	int heuristicValue;
	Node* parent;

	Node(Vector2Int _pos, int _cost, int hValue, Node* _parent = nullptr)
		: pos(_pos), cost(_cost), heuristicValue(hValue), parent(_parent){}

	int Evaluate() const { return cost + heuristicValue; }
};

/// <summary>
/// ハッシュ値
/// </summary>
struct Hash
{
	size_t operator()(const Vector2Int& v)const { return v.x * 97 + v.y; }
};

struct Compare
{
	bool operator()(const Node* a, const Node* b) { return a->Evaluate() > b->Evaluate(); }
};

inline int GetHeuristic(const Vector2Int& a, const Vector2Int& b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

inline bool IsValidPosition(Vector2Int& pos, _mapInfo& mapInfo )
{
	return pos.x >= 0 && pos.y >= 0 && pos.x <= mapInfo.width-1 && pos.y <= mapInfo.height-1;
}
#pragma endregion

#pragma region ヘルパー関数


/// ワールド座標からスクリーン座標へ変換
inline Vector2Int GetScreenPos(VECTOR pos) 
{
	Vector2Int result = Vector2Int();

	VECTOR buff = ConvWorldPosToScreenPos(pos);
	result.x = buff.x;
	result.y = buff.y;
	return result;
};

/// 配列座標をワールド座標(グリッドフィールド中央)に変換
inline VECTOR ArrayPos2WorldPosCenter(const int x, const int y)
{
	VECTOR result = VGet(x * MAP_UNIT + MAP_UNIT / 2, 0, y * MAP_UNIT + MAP_UNIT / 2);
		return result;
}

/// <summary>
/// 配列座標をワールド座標に変換
/// </summary>
inline VECTOR ArrayPos2WorldPos(const int x, const int y)
{
	VECTOR result = VGet(x * MAP_UNIT, 0, y * MAP_UNIT);
	return result;
}

inline Vector2Int WorldPos2ArrayPos(VECTOR pos)
{
	Vector2Int result =
	{
		floor(pos.x / MAP_UNIT),
		floor(pos.z / MAP_UNIT)
	};

	return result;
}

/// 絶対パスを取得
inline string GetExecutablePath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH); //絶対パスを取得
	string path(buffer);
	return path.substr(0, path.find_last_of("\\/")); //ディレクトリ部分を抽出
}

/// <summary>
/// VECTORを指定のけたで四捨五入する
/// </summary>
/// <param name="vec"></param>
/// <param name="decimal"></param>
/// <returns></returns>
inline VECTOR Round(VECTOR vec, int decimal = 0)
{
	VECTOR result = VScale(vec, pow(10.0, decimal));

	result = VGet
	(
		round(result.x),
		round(result.y),
		round(result.z)
	);

	result = VScale(result, pow(0.1, decimal));

	return result;
}
/// <summary>
/// ターゲット座標が指定した矩形の領域内か判定
/// </summary>
/// <param name="targetPos"> ターゲット座標</param>
/// <param name="vertex1"> 矩形の左上座標</param>
/// <param name="vertex2"> 矩形の右下</param>
inline bool CheckInRect(Vector2Int& targetPos, Vector2Int& vertex1, Vector2Int& vertex2)
{
	return targetPos.x >= vertex1.x && targetPos.x <= vertex2.x
		&& targetPos.y >= vertex1.y && targetPos.y <= vertex2.y;
}
/// <summary>
/// ターゲット座標が指定した矩形の領域内か判定
/// </summary>
/// <param name="targetPos">ターゲット座標</param>
/// <param name="rect">矩形の構造体</param>
/// <returns></returns>
inline bool CheckInRect(Vector2Int& targetPos, RECTInt rect)
{
	return targetPos.x >= rect.left && targetPos.x <= rect.right
		&& targetPos.y >= rect.top && targetPos.y <= rect.bottom;
}

inline float RadtoDeg(float radian)
{
	return radian * 180.0f / DX_PI_F;
}

inline float DegtoRad(float degree)
{
	return degree * DX_PI_F / 180.0f;
}
#pragma endregion
