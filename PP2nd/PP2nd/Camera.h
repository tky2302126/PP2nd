#pragma once
#include "define.h"
#include "manager.h"

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
	float AngleV;
	float AngleH;
	VECTOR position;
	VECTOR lookPosition;
	Vector2Int oldMousePos;
};

