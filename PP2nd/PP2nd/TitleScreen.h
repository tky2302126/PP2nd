#pragma once
#include "define.h"
#include "manager.h"

class HUD;
class Map;
class Camera;

enum TitleSequence
{
	Title,
	Menu
};

/// <summary>
/// タイトル画面の描画
/// </summary>
class TitleScreen 
{
public:
	void Init();
	void UnInit();
	void Update();
private:
	/// 必要なリソース
	UniquePtr<Camera> camerauPtr; /// カメラ
	UniquePtr<Map> mapUPtr; /// マップ
	TitleSequence currentSequence = Title; /// シーケンス
	int buttonGH; /// ボタン用のイメージソース
	int confirmGH; /// 確認UI用のイメージソース
	int arrowImageGH; /// 配置を促す矢印のイメージソース
};

