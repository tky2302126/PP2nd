#pragma once
#include "define.h"
#include "manager.h"

/// <summary>
/// カメラの制御
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void UnInit();
	void Update();

	VECTOR GetPosition();
private:
	VECTOR position;
	VECTOR lookPosition;
	Vector2Int oldMousePos;
};

