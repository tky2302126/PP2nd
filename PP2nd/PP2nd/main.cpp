#include "DxLib.h"
#include "manager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	{ return -1; }

	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	SetMouseDispFlag(TRUE);

	SceneManager& sceneMPtr = SceneManager::GetInstance();
	sceneMPtr.Init();

	InputSystem& inputSystemPtr = InputSystem::GetInstance();
	inputSystemPtr.Init();

#if _DEBUG
	sceneMPtr.Load(SceneName::Test);
#endif

	while (true)
	{
		ClearDrawScreen();

		sceneMPtr.Update();

		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}