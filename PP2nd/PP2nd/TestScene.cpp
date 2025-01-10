#include "TestScene.h"

TestScene::TestScene()
{

}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	DrawFormatString(0, 0, 65535, " テストシーン");


	int mouseX, mouseY;
	Vector2Int currentMousePos = InputSystem::GetInstance().GetMousePosition();
	mouseX = currentMousePos.x;
	mouseY = currentMousePos.y;

}
