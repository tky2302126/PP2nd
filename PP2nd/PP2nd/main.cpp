#include "DxLib.h"
#include "manager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	{ return -1; }

	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(TRUE);
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	SetUseBackCulling(TRUE);
	SetBackgroundColor(128, 128, 128, 128);

	SetTransColor(255, 0, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

#pragma region ManagerÇÃèÄîı
	SceneManager& sceneMPtr = SceneManager::GetInstance();
	sceneMPtr.Init();

	InputSystem& inputSystemPtr = InputSystem::GetInstance();
	inputSystemPtr.Init();

	GameManager& gameMPtr = GameManager::GetInstance();
	gameMPtr.Init();
	ItemInfo buff;
	buff.name = ItemList::Cube;
	buff.num = 99;
	gameMPtr.SetItemInfo(buff);
#pragma endregion




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