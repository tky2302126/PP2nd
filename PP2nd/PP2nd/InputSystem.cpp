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
}

Vector2Int InputSystem::GetMousePosition()
{
    return Vector2Int();
}

InputSystem& InputSystem::GetInstance()
{
    if (Instance == nullptr) 
    {
        Instance = make_unique<InputSystem>();
    }

    return *Instance;
}
