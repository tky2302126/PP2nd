#include "InputSystem.h"

unique_ptr<InputSystem> InputSystem::Instance = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Init()
{
}

void InputSystem::UnInit()
{
}

void InputSystem::Update()
{
    GetMousePoint(&currentInfo.position.x, &currentInfo.position.y);

#pragma region left
    /// None || canceled -> Started
    if ((currentInfo.state.left == None || currentInfo.state.left == Canceled) && MouseInputLeft())
    {
        currentInfo.state.left = Started;
    }
    else if ((currentInfo.state.left == Started) && MouseInputLeft())
    {
        currentInfo.state.left = Performed;
    }
    else if ((currentInfo.state.left == Performed || currentInfo.state.left == Started) && !MouseInputLeft())
    {
        currentInfo.state.left = Canceled;
    }
    else if ((currentInfo.state.left == Canceled) && !MouseInputLeft())
    {
        currentInfo.state.left = None;
    }
#pragma endregion

#pragma region right
    if ((currentInfo.state.right == None || currentInfo.state.right == Canceled) && MouseInputRight())
    {
        currentInfo.state.right = Started;
    }
  
    else if ((currentInfo.state.right == Started) && MouseInputRight())
    {
        currentInfo.state.right = Performed;
    }
    else if ((currentInfo.state.right == Performed || currentInfo.state.right == Started) && !MouseInputRight())
    {
        currentInfo.state.right = Canceled;
    }
    else if ((currentInfo.state.right == Canceled) && !MouseInputRight())
    {
        currentInfo.state.right = None;
    }
#pragma endregion 
}

Vector2Int InputSystem::GetMousePosition()
{
    return currentInfo.position;
}

MouseState InputSystem::GetMouseState()
{
    return currentInfo.state;
}

MouseInfo InputSystem::GetMouseInfo()
{
    return currentInfo;
}

InputSystem& InputSystem::GetInstance()
{
    if (Instance == nullptr) 
    {
        Instance = make_unique<InputSystem>();
    }

    return *Instance;
}

bool InputSystem::MouseInputLeft()
{
    return GetMouseInput() & MOUSE_INPUT_LEFT;
}

bool InputSystem::MouseInputRight()
{
    return GetMouseInput() & MOUSE_INPUT_RIGHT;
}
