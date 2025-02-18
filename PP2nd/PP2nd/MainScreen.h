#pragma once
#include "define.h"
#include "Camera.h"

class HUD;
class Map;
class Camera;

/// <summary>
/// ゲームメインの画面の描画を管理する
/// !todo マップ情報からカメラ、フィールドの描画を行う
/// </summary>
class MainScreen
{
public:
	void Init(const _mapInfo& mapInfo);
	void Init(const int day);
	void UnInit();
	void Draw();
	void Update();
private:
	UniquePtr<HUD> hudUPtr;
	UniquePtr<Map> mapUPtr;
	UniquePtr<Camera> cameraUPtr;
	int stageClearGH;
	int gameOverGH;
};

