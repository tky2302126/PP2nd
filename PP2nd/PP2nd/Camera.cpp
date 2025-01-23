#include "Camera.h"

Camera::Camera()
	:oldMousePos(Vector2Int()),position(VECTOR()),initPos(VECTOR())
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
    //カメラの初期化
	//マップ中央にしたい
	position.x = CAMERA_MIN_X;
	position.y = CAMERA_HEIGHT;
	position.z = CAMERA_MIN_Z-CAMERA_Z_OFFSET; 
	
	oldMousePos.x = 0;
	oldMousePos.y = 0;
	
}

/// <summary>
/// マップの大きさに合わせてカメラの位置を初期化する
/// </summary>
/// <param name="mapInfo"></param>
void Camera::Init(const _mapInfo& mapInfo)
{
	position.x = mapInfo.width*MAP_UNIT/2;
	position.y = CAMERA_HEIGHT;
	position.z = mapInfo.height*MAP_UNIT/2 - CAMERA_Z_OFFSET;

	initPos = position;

	oldMousePos.x = 0;
	oldMousePos.y = 0;
	
	SetupCamera_Perspective(DX_PI/2);
	/// カメラの方向ベクトルをGameManagerに格納
	VECTOR cameraDirection = GetDirection(CAMERA_VROTATE, 0);
	GameManager::GetInstance().SetCameraDirection(cameraDirection);
}

void Camera::UnInit()
{
}

void Camera::Update()
{
#pragma region デバック操作
	///方向キーでカメラの座標を移動
	/// if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	/// {
	/// 	position.z += 20.0f;
	/// 	lookPosition.z += 20.0f;
	/// }
	/// if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	/// {
	/// 	position.z -= 20.0f;
	/// 	lookPosition.z -= 20.0f;
	/// }
	/// if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	/// {
	/// 	position.x -= 20.0f;
	/// 	lookPosition.x -= 20.0f;
	/// }
	/// if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	/// {
	/// 	position.x += 20.0f;
	/// 	lookPosition.x += 20.0f;
	/// }
	/// if (CheckHitKey(KEY_INPUT_Q))
	/// {
	/// 	position.y -= 20.0f;
	/// 	if (position.y <= 0) { position.y = 0; }
	/// 	
	/// }
	/// if (CheckHitKey(KEY_INPUT_E))
	/// {
	/// 	position.y += 20.0f;
	/// 	
	/// }
#pragma endregion
	/// マウスの入力でカメラと注視点の座標を移動する
	/// ! カメラの移動に下限上限を決める
	MouseInfo currentInput = InputSystem::GetInstance().GetMouseInfo();

	/// マウスがHUDの範囲の時入力を受けない
	if (currentInput.position.y <= HUD_AREA_TOP || currentInput.position.y>= HUD_AREA_BOTTOM)
	{
		move = false;
		return;
	}

	///

	InputState leftState = currentInput.state.left;

	if(leftState == Started)
	{
		oldMousePos = currentInput.position;
		move = true;
	}
	else if(leftState == Performed && move)
	{
		int durationX = currentInput.position.x - oldMousePos.x;
		int durationY = currentInput.position.y - oldMousePos.y;
		
		//if((position.x-durationX * 2.0f) >= CAMERA_MIN_X)
		{
			position.x -= durationX * 2.0f;
		}

		//if((position.z + durationY * 2.0f) >= CAMERA_MIN_Z)
		{
			position.z += durationY * 2.0f;
		}
		oldMousePos = currentInput.position;
	}
	else if(leftState == Canceled && move)
	{
		move = false;
	}
	
	/// マップ中央にカメラを戻す
	if(CheckHitKey(KEY_INPUT_R))
	{
		position = initPos;
	}

	float vRotate = DegtoRad(CAMERA_VROTATE);
	 //float hRotate = DegtoRad(0.f);
	SetCameraPositionAndAngle(position, vRotate, 0, 0);


}

VECTOR Camera::GetPosition()
{
	return position;
}

VECTOR Camera::GetDirection(float vRotate, float hRotate)
{
	float vRotateRad = DegtoRad(vRotate);
	float hRotateRad = DegtoRad(hRotate);

	VECTOR direction = VGet
	(
		cosf(vRotateRad)*sinf(hRotateRad),
		-sinf(vRotateRad),
		cosf(vRotateRad) * cosf(hRotateRad)
	);
	return direction;
}

