#pragma once
#include "define.h"
#include "manager.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"

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
	UniquePtr<Camera> cameraUPtr;
	UniquePtr<HUD> hudUPtr;
	UniquePtr<Map> mapUPtr;
	SceneName currentSequence = Title; /// シーケンス
	SceneName oldSequence;
	int buttonGH; /// ボタン用のイメージソース
	int confirmGH; /// 確認UI用のイメージソース
	int arrowImageGH; /// 配置を促す矢印のイメージソース
	float holdThreshold = 2.5f;
	int pressStart = 0;
};

