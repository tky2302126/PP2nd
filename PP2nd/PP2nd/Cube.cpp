#include "Cube.h"

Cube::Cube()
    :MHandle(-1)
{
}

Cube::~Cube()
{
}

void Cube::Init()
{
}

void Cube::Init(int _Ghandle) 
{
    MHandle = _Ghandle;
}

void Cube::Init(int _Ghandle, VECTOR _pos)
{
    MHandle = _Ghandle;
    pos = _pos;
    /// 埋まらないようにあげる
    pos.y += MAP_UNIT / 2;
}

void Cube::UnInit()
{
}

void Cube::OnEnter() const 
{
}

void Cube::OnExit() const
{
}

void Cube::Draw() const
{
    MV1SetPosition(MHandle,pos);
    MV1DrawModel(MHandle);
}

void Cube::Update() const
{
    /// カメラの描画範囲なら実行
    Draw();
}

/// <summary>
/// 確認UIを表示する
/// ゲームスピードを遅くする
/// </summary>
void Cube::Confirm() const
{
    /// いったん登録のみ
    GameManager::GetInstance().AddTerrainInfo(TerrainList::CUBE, pos);
}

int& Cube::GetMHandle() const
{
    int MHandle = -1;
    return MHandle;
}
