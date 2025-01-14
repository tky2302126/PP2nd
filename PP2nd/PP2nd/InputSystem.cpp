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

    /// None || canceled -> Started
    if ((currentInfo.state.left == None || currentInfo.state.left == Canceled) && MouseInputLeft())
    {
        currentInfo.state.left = Started;
    }

    if ((currentInfo.state.right == None || currentInfo.state.right == Canceled) && MouseInputRight())
    {
        currentInfo.state.right = Started;
    }

    /// Started -> performed
    if ((currentInfo.state.left == Started) && MouseInputLeft())
    {
        currentInfo.state.left = Performed;
    }

    if ((currentInfo.state.right == Started) && MouseInputRight())
    {
        currentInfo.state.right = Performed;
    }

    /// Started || performed ->canceled
    if ((currentInfo.state.left == Started || currentInfo.state.left == Performed) && !MouseInputLeft())
    {
        currentInfo.state.left = Canceled;
    }

    if ((currentInfo.state.right == Started || currentInfo.state.right == Performed) && !MouseInputRight())
    {
        currentInfo.state.right = Canceled;
    }
    /// canceled -> None
    if ((currentInfo.state.left == Canceled) && !MouseInputLeft())
    {
        currentInfo.state.left = None;
    }

    if ((currentInfo.state.right == Canceled) && !MouseInputRight())
    {
        currentInfo.state.right = None;
    }
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
