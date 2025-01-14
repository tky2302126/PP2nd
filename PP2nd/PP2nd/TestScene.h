#pragma once
#include "define.h"
#include "Scene.h"
#include "manager.h"

class Camera;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update();

private:
	Camera* cameraPtr;
};

