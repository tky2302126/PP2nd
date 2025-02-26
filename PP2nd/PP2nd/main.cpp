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
	SetAlwaysRunFlag(TRUE);
	SetBackgroundColor(128, 128, 128, 128);
	SetWaitVSyncFlag(FALSE);

	SetTransColor(255, 0, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

#pragma region Managerの準備
	SceneManager& sceneMPtr = SceneManager::GetInstance();
	sceneMPtr.Init();

	InputSystem& inputSystemPtr = InputSystem::GetInstance();
	inputSystemPtr.Init();

	GameManager& gameMPtr = GameManager::GetInstance();
	gameMPtr.Init();
	
	TimeManager& timeMPtr = TimeManager::GetInstance();

	EnemyManager& enemyMPtr = EnemyManager::GetInstance();
	enemyMPtr.Init();

	AudioManager& audioMPtr = AudioManager::GetInstance();
	audioMPtr.Init();
#ifdef _DEBUG
	enemyMPtr.InitTest();

#endif // _DEBUG

#pragma endregion



	// 提出用にコメントアウト
// #if _DEBUG
	sceneMPtr.Load(SceneName::Title);
// #endif
	while (true)
	{
		ClearDrawScreen();

		sceneMPtr.Update();

		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
	}
#pragma region Managerの解放
	/// スマートポインタの解放がDxlib_endよりも遅いので
	/// ここで実行
	
	audioMPtr.UnInit();
	enemyMPtr.UnInit();
	gameMPtr.UnInit();
	inputSystemPtr.UnInit();
	sceneMPtr.UnInit();
	timeMPtr.UnInit();

#pragma endregion


	DxLib_End();

	return 0;
}