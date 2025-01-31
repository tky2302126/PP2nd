#include "Cube.h"

Cube::Cube()
    :MHandle(-1),
    pos(VECTOR())
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

    /// クリックされたら確認UIを表示
}

/// <summary>
/// 設置の確認
/// ゲームスピードを遅くする
/// </summary>
void Cube::Confirm() const
{
    /// 確認UIを表示する

    /// いったん登録のみ
    /// 試しに置いて進行ルートが閉鎖されないか確認

    GameManager::GetInstance().AddTerrainInfo(TerrainList::CUBE, pos);
}

int& Cube::GetMHandle() const
{
    int MHandle = -1;
    return MHandle;
}
