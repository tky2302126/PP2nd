#pragma once
#include "define.h"

enum InputState
{
	None,
	Started,
	Performed,
	Canceled
};

typedef struct
{
	InputState left;
	InputState right;
}MouseState;

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
	static InputSystem& GetInstance();
	
private:
	int mouseX;
	int mouseY;
	MouseState mouseState;

	static unique_ptr<InputSystem> Instance;

};

