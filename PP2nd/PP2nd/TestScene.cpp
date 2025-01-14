#include "TestScene.h"
#include "Camera.h"

TestScene::TestScene()
{
	cameraPtr = new Camera();
	cameraPtr->Init();
}

TestScene::~TestScene()
{
	cameraPtr->UnInit();
	delete cameraPtr;
}

void TestScene::Update()
{
	DrawFormatString(0, 0, 65535, " テストシーン");
	InputSystem::GetInstance().Update();
#pragma region マウス確認
	/// MouseInfo mouseInfo = InputSystem::GetInstance().GetMouseInfo();
	/// 
	/// DrawFormatString(0, 30, GetColor(255, 255, 255), "mouse position( %d, %d)", mouseInfo.position.x, mouseInfo.position.y);
	/// DrawFormatString(0, 60, GetColor(255, 255, 255), "mouse state( %d , %d)",mouseInfo.state.left,mouseInfo.state.right );
#pragma endregion


#pragma region カメラ確認
	int XAxizcolor = GetColor(255, 128, 255);
	int ZAxizColor = GetColor(128, 255, 255);

	int fieldwidth = 8000;
	int gridSize = MAP_UNIT;

	cameraPtr->Update();
	

	for (int i = 0; i < fieldwidth; i += gridSize)
	{
		DrawLine3D(VGet(i, 0, 0), VGet(i, 0, fieldwidth), XAxizcolor);
		DrawLine3D(VGet(0, 0, i), VGet(fieldwidth, 0, i), ZAxizColor);
	}

	VECTOR cameraPos = cameraPtr->GetPosition();

	DrawFormatString(0, 30, GetColor(255, 255, 255), "camera position( %f, %f, %f)",cameraPos.x , cameraPos.y , cameraPos.z);
#pragma endregion
}
