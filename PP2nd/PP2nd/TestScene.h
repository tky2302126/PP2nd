#pragma once
#include "define.h"
#include "Scene.h"
#include "manager.h"

class Camera;
class HUD;
class Map;
class Box;
class MainScreen;

/// <summary>
/// 開発用のデバッグシーン
/// </summary>
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() const override;

private:
	Camera* cameraPtr;
	UniquePtr<HUD> hudUPtr;
	UniquePtr<Map> mapUPtr;
	UniquePtr<MainScreen> mainScreenUPtr;
};

