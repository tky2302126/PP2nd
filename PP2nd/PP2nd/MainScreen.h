#pragma once
#include "define.h"

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
	void UnInit();
	void Draw();
	void Update();
private:
	UniquePtr<HUD> hudUPtr;
	UniquePtr<Map> mapUPtr;
	UniquePtr<Camera> cameraUPtr;
};

