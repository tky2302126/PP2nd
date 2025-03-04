#include "DxLib.h"
#include "manager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)	{ return -1; }
	if (Effekseer_Init(2000) == -1) { DxLib_End(); return -1; }

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
	SetUseDirect3DVersion(DX_DIRECT3D_11);

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
#if _DEBUG
	enemyMPtr.InitTest();

#endif // _DEBUG

#pragma endregion



	/// デバッグとexeで切り替え
 #if _DEBUG
	//sceneMPtr.Load(SceneName::Test);
	sceneMPtr.Load(SceneName::Title);
#else
	sceneMPtr.Load(SceneName::Title);
 #endif
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

	Effkseer_End();
	DxLib_End();

	return 0;
}