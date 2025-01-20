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

	void Enable();
	void Disable();
	
	Vector2Int GetMousePosition();
	MouseState GetMouseState();
	MouseInfo GetMouseInfo();
	static InputSystem& GetInstance();
	
private:
	MouseInfo currentInfo;
	bool enable = true;

	static unique_ptr<InputSystem> Instance;

	bool MouseInputLeft();
	bool MouseInputRight();
	

};

