#pragma once
#include "define.h"
#include "manager.h"

class HUD;
class Map;

/// <summary>
/// タイトル画面の描画
/// </summary>
class TitleScreen 
{
public:
	void Init();
	void UnInit();
	void Draw();
	void Update();
private:
	/// 必要なリソース
	/// UniquePtr<Camera> cameraUPtr; /// カメラ
	/// UniquePtr<Map> mapUPtr; /// マップ
	/// UniquePtr<HUD> hudUPtr; /// HUD
	SceneName currentSequence = Title; /// シーケンス
	int buttonGH; /// ボタン用のイメージソース
	int confirmGH; /// 確認UI用のイメージソース
	int arrowImageGH; /// 配置を促す矢印のイメージソース
};

