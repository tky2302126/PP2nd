#pragma once
#include "define.h"
#include "manager.h"
#include "Camera.h"
#include "HUD.h"
#include "Map.h"
#include "Button.h"

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
	void MoveCamera();
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
	
	int titleLogoGH;
	RECTInt logoStart = {-TITLELOGO_SIZE, 0, WINDOW_WIDTH/2 - TITLELOGO_SIZE/2, WINDOW_WIDTH / 2 + TITLELOGO_SIZE / 2 };
	RECTInt logoEnd = {0, TITLELOGO_SIZE, WINDOW_WIDTH / 2 - TITLELOGO_SIZE / 2, WINDOW_WIDTH / 2 + TITLELOGO_SIZE / 2 };


	// 補間用変数
	VECTOR startPos, endPos;
	VECTOR startTarget, endTarget;
	float moveDuration = 2.5f;
	double elapsedTime = 0.0f;
	bool isMoving = false;
	std::vector<Button*> menuButtonPtrVec;
	bool isActive = true;
	SceneName nextScene = (SceneName) - 1;

	void OnPressStageButton();
};

