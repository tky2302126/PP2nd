#include "Cube.h"

Cube::Cube()
    :GHandle(-1)
{
}

Cube::~Cube()
{
}

void Cube::Init()
{
}

void Cube::UnInit()
{
}

void Cube::OnEnter()
{
}

void Cube::OnExit()
{
}

int& Cube::GetGHandle()
{
    return GHandle;
}

int& Cube::GetMHandle()
{
    int MHandle = -1;
    return MHandle;
}
