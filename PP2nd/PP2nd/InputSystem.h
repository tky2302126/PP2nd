#pragma once
#include "define.h"


/// <summary>
/// “ü—Íî•ñ‚ğŠÄ‹
/// </summary>
class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void Init();
	void UnInit();

	void Update();
	
	Vector2Int GetMousePosition();
	MouseState GetMouseState();
	MouseInfo GetMouseInfo();
	static InputSystem& GetInstance();
	
private:
	MouseInfo currentInfo;

	static unique_ptr<InputSystem> Instance;

	bool MouseInputLeft();
	bool MouseInputRight();
	

};

