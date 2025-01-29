#include "Start.h"
#include "GameManager.h"
void Start::Init()
{
}

void Start::Init(Vector2Int _pos)
{
    pos = _pos;
    SearchRoute();
}

void Start::UnInit()
{
}

/// <summary>
/// ゲームマネージャからマップ情報を受け取り、ルートを設定する
/// Aスター法
/// </summary>
void Start::SearchRoute()
{
    
}

bool Start::ReachGoal()
{
    return false;
}
