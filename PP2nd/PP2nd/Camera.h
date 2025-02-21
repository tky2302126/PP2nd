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
	void Update(SceneName);
private:
	VECTOR position;
	VECTOR initPos;
	VECTOR targetPos;
	VECTOR initTargetPos;
	Vector2Int oldMousePos;
	float elevationAngle = DegtoRad(CAMERA_VROTATE);
	float azimuthAngle;
	bool move = false;
	bool rotate = false;
	float moveSpeed = 2.0f;
	float rotateSpeed = 1.0f;
};

