#include "Camera.h"

Camera::Camera()
	:oldMousePos(Vector2Int()),position(VECTOR()),initPos(VECTOR()),
	targetPos(VECTOR()),azimuthAngle(0.0),initTargetPos(VECTOR())
{
}

Camera::~Camera()
{
}

/// 近いカメラで配置場所を示す
void Camera::Init()
{
	position = { CAMERA_MIN_X, CAMERA_HEIGHT / 2,CAMERA_MIN_Z - CAMERA_Z_OFFSET / 2 };

	oldMousePos = { 0, 0 };

	targetPos = VGet(CAMERA_MIN_X, 0, CAMERA_MIN_Z);
	
}

/// <summary>
/// マップの大きさに合わせてカメラの位置を初期化する
/// </summary>
/// <param name="mapInfo"></param>
void Camera::Init(const _mapInfo& mapInfo)
{
	position = { mapInfo.width * MAP_UNIT / 2, CAMERA_HEIGHT, mapInfo.height * MAP_UNIT / 2 - CAMERA_Z_OFFSET };

	initPos = position;

	targetPos = VGet(mapInfo.width * MAP_UNIT / 2,
					 0,
					 mapInfo.height * MAP_UNIT / 2);
	initTargetPos = targetPos;

	oldMousePos.x = 0;
	oldMousePos.y = 0;
	azimuthAngle = DegtoRad(-90.f);
	SetupCamera_Perspective((float)DX_PI/2);
}

void Camera::UnInit()
{
}

/// <summary>
/// カメラの場所を変更するスクリプト
/// </summary>
/// <param name="destination">カメラの位置</param>
/// <param name="targetPosDestination">注視点</param>
void Camera::ManualMove(const VECTOR destination,const VECTOR targetPosDestination)
{
	position = destination;
	targetPos = targetPosDestination;
}

void Camera::Update()
{
	/// マウスの入力でカメラと注視点の座標を移動する
	/// ! カメラの移動に下限上限を決める
	MouseInfo currentInput = Input().GetMouseInfo();

	/// マウスがHUDの範囲の時入力を受けない
	if (currentInput.position.y <= HUD_AREA_TOP || currentInput.position.y>= HUD_AREA_BOTTOM)
	{
		move = false;
		rotate = false;
		return;
	}
#pragma region カメラの移動
	InputState leftState = currentInput.state.left;

	if(leftState == Started)
	{
		oldMousePos = currentInput.position;
		move = true;
	}
	else if(leftState == Performed && move)
	{
		int dx = currentInput.position.x - oldMousePos.x;
		int dy = currentInput.position.y - oldMousePos.y;
		
		VECTOR forward = { cosf(azimuthAngle), 0, sinf(azimuthAngle) };
		VECTOR right = { -sinf(azimuthAngle), 0, cosf(azimuthAngle) };

		targetPos.x -= (right.x * dx + forward.x * dy) * moveSpeed;
		targetPos.z -= (right.z * dx + forward.z * dy) * moveSpeed;

		oldMousePos = currentInput.position;
	}
	else if(leftState == Canceled && move)
	{
		move = false;
	}
#pragma endregion
	
#pragma region カメラの回転
	InputState rightState = currentInput.state.right;

	if (rightState == Started)
	{
		oldMousePos = currentInput.position;
		rotate = true;
	}
	else if (rightState == Performed && rotate)
	{
		int durationX = currentInput.position.x - oldMousePos.x;
		azimuthAngle += DegtoRad(durationX * 1.0f);
		oldMousePos = currentInput.position;
	}
	else if (rightState == Canceled && rotate)
	{
		rotate = false;
	}


	// 球面座標をデカルト座標に変換
	float x = CAMERA_RADIUS * cosf(elevationAngle) * cosf(azimuthAngle);
	float y = CAMERA_RADIUS * sinf(elevationAngle);
	float z = CAMERA_RADIUS * cosf(elevationAngle) * sinf(azimuthAngle);

	position = { x, y, z };
	position = VAdd(position, targetPos);
#pragma endregion

	/// マップ中央にカメラを戻す
	if(CheckHitKey(KEY_INPUT_R))
	{
		position = initPos;
		targetPos = initTargetPos;
		azimuthAngle = 0.0f;
	}

	// SetCameraPositionAndAngle(position, elevationAngle, 0, 0);
	SetCameraPositionAndTarget_UpVecY(position, targetPos);
	
	GM().SetCameraPosition(position);

}

/// <summary>
/// タイトルシーンで使用
/// シーケンスによってカメラの挙動を変える->manualmoveに移管したため不要になった
/// </summary>
void Camera::Update(SceneName sequence)
{

	SetCameraPositionAndTarget_UpVecY(position, targetPos);

	GM().SetCameraPosition(position);
}

