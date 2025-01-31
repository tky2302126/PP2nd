#include "TestEnemy.h"

TestEnemy::TestEnemy()
	:myRoute(vector<Vector2Int>())
{
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Init(int _Mhandle =-1)
{
}

void TestEnemy::Draw() const
{
}

void TestEnemy::Move() const
{
}

void TestEnemy::Update() const
{
}

void TestEnemy::SetRoute(vector<Vector2Int> _route)
{
	myRoute = _route;
}
