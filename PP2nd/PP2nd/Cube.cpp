#include "Cube.h"
#include "Camera.h"
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
    /// staticメンバーがロードされていない場合、ロードする

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
    auto currentInput = InputSystem::GetInstance().GetMouseInfo();

    Vector2Int screenPos = GetScreenPos(pos);
    DrawFormatString(0, 180, GetColor(255, 255, 255), "mousePos: %d , %d", currentInput.position.x, currentInput.position.y);
    DrawFormatString(0, 200, GetColor(255, 255, 255), "ItemScreenPos: %d, %d", screenPos.x, screenPos.y);
    
    /// カメラの位置によってクリックの猶予値を変えたい
    if(currentInput.state.left == Started && abs(currentInput.position.x-screenPos.x) <= 20 && abs(currentInput.position.y - screenPos.y) <= 20)
    {
        DrawFormatString(0, 220, GetColor(255, 255, 255), "Clicked");
    }

    /// 確認UIを表示する
    if(isConfirm)
    {
        DrawExtendGraph(screenPos.x-CONFIRM_PANEL_OFFSET-CONFIRM_PANEL_SIZE/2,screenPos.y-CONFIRM_PANEL_OFFSET-CONFIRM_PANEL_SIZE/2,
            screenPos.x - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2, screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2,
            gHandleCross,FALSE);
        DrawExtendGraph(screenPos.x + CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2, screenPos.y - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2,
            screenPos.x + CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2, screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2,
            gHandleCheck, FALSE);
    }

}

/// <summary>
/// 設置の確認
/// ゲームスピードを遅くする
/// </summary>
void Cube::Confirm()
{
    /// カメラの中央付近に来るようにカメラを動かす(優先順位:低)
    /// 自分のPosを渡し、ｘを一致、ｚをCameraOFFSET分離す
        
    isConfirm = true;

    /// 試しに置いて進行ルートが閉鎖されないか確認

    /// いったん登録のみ
    GameManager::GetInstance().AddTerrainInfo(TerrainList::CUBE, pos);
}

int& Cube::GetMHandle() const
{
    int MHandle = -1;
    return MHandle;
}
