#include "Camera.h"

Camera::Camera()
	:lookPosition(VECTOR()),oldMousePos(Vector2Int()),position(VECTOR())
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
	position.z = CAMERA_MIN_Z+CAMERA_Z_OFFSET; 
	lookPosition.x = CAMERA_MIN_X;
	lookPosition.y = 0.0f;
	lookPosition.z = CAMERA_MIN_Z;
	
	oldMousePos.x = 0;
	oldMousePos.y = 0;
	
}

/// <summary>
/// マップの大きさに合わせてカメラの位置を初期化する
/// </summary>
/// <param name="mapInfo"></param>
void Camera::Init(const _mapInfo& mapInfo)
{
	position.x = CAMERA_MIN_X;
	position.y = CAMERA_HEIGHT;
	position.z = CAMERA_MIN_Z + CAMERA_Z_OFFSET;
	lookPosition.x = CAMERA_MIN_X;
	lookPosition.y = 0.0f;
	lookPosition.z = CAMERA_MIN_Z;


	oldMousePos.x = 0;
	oldMousePos.y = 0;
	
	//SetupCamera_Ortho(MAP_HEIGHT);
	SetupCamera_Perspective(DX_PI/2);
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

	InputState leftState = currentInput.state.left;

	if(leftState == Started)
	{
		oldMousePos = currentInput.position;
	}
	else if(leftState == Performed)
	{
		int durationX = currentInput.position.x - oldMousePos.x;
		int durationY = currentInput.position.y - oldMousePos.y;
		
		//if((position.x-durationX * 2.0f) >= CAMERA_MIN_X)
		{
			position.x -= durationX * 2.0f;
			lookPosition.x -= durationX * 2.0f;
		}

		//if((position.z + durationY * 2.0f) >= CAMERA_MIN_Z)
		{
			position.z += durationY * 2.0f;
			lookPosition.z += durationY * 2.0f;
		}
		oldMousePos = currentInput.position;
	}
	
	float vRotate = DegtoRad(60.0f);
	float hRotate = DegtoRad(0.f);
	SetCameraPositionAndAngle(position, vRotate, hRotate, 0);
	//SetCameraPositionAndTargetAndUpVec(position, lookPosition,VGet(0,0.5f,1)); ///見下ろし型のカメラ

}

VECTOR Camera::GetPosition()
{
	return position;
}

