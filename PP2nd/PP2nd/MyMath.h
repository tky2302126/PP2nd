#pragma once
#include "define.h"

inline VECTOR GridtoVECTOR()
{
	return VECTOR();
}

inline float RadtoDeg(float radian)
{
	return radian * 180.0f / DX_PI;
}

inline float DegtoRad(float degree)
{
	return degree* DX_PI / 180.0f;
}