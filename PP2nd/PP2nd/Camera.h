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
	void Init(const _mapInfo& mapInfo);
	void UnInit();
	void Update();
private:
	VECTOR position;
	VECTOR initPos;
	Vector2Int oldMousePos;
	float vRotate = DegtoRad(CAMERA_VROTATE);
	bool move = false;
	bool rotate = false;

};

