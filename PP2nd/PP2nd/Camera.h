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
	VECTOR GetRotation();
private:
	VECTOR position;
	VECTOR lookPosition;
	float VRotate;
	float HRotate;
	float TRotate;
	Vector2Int oldMousePos;
};

