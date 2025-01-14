#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
    //カメラの初期化
    AngleH = DX_PI_F;
    AngleV = 0.0f;
	position.x = 0.0f;
	position.y = 1800.0f;
	position.z = -1000.0f;
	lookPosition.x = 0.0f;
	lookPosition.y = 0.0f;
	lookPosition.z = 0.0f;
	
	oldMousePos.x = 0.0f;
	oldMousePos.y = 0.0f;
}

void Camera::UnInit()
{
}

void Camera::Update()
{
	/// // 方向キーでカメラの座標を移動
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

	/// マウスの入力でカメラと注視点の座標を移動する
	MouseInfo currentInput = InputSystem::GetInstance().GetMouseInfo();

	InputState leftState = currentInput.state.left;

	if(leftState == Started)
	{
		oldMousePos = currentInput.position;
	}

	if(leftState == Performed)
	{
		int durationX = currentInput.position.x - oldMousePos.x;
		int durationY = currentInput.position.y - oldMousePos.y;
		
		position.x -= durationX * 2.0f;
		lookPosition.x -= durationX * 2.0f;
		
		position.z += durationY * 2.0f;
		lookPosition.z += durationY * 2.0f;

		oldMousePos = currentInput.position;
	}
	

	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

VECTOR Camera::GetPosition()
{
	return position;
}
