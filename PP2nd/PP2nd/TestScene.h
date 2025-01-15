#pragma once
#include "define.h"
#include "Scene.h"
#include "manager.h"

class Camera;

/// <summary>
/// 開発用のデバッグシーン
/// </summary>
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update();

private:
	Camera* cameraPtr;
};

