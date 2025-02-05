#include "Cube.h"
#include "Camera.h"
#include "Map.h"
Cube::Cube()
    :MHandle(-1),
    pos(VECTOR()),
    mapPtr(nullptr)
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

void Cube::Init(int _Ghandle, VECTOR _pos, Map* _mapPtr)
{
    MHandle = _Ghandle;
    pos = _pos;
    /// 埋まらないようにあげる
    pos.y += MAP_UNIT / 2;
    mapPtr = _mapPtr;
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

void Cube::Update()
{
    /// カメラの描画範囲なら実行
    Draw();

    /// クリックされたら確認UIを表示
    auto currentInput = InputSystem::GetInstance().GetMouseInfo();

    Vector2Int screenPos = GetScreenPos(pos);
    DrawFormatString(0, 180, GetColor(255, 255, 255), "mousePos: %d , %d", currentInput.position.x, currentInput.position.y);
    DrawFormatString(0, 200, GetColor(255, 255, 255), "ItemScreenPos: %d, %d", screenPos.x, screenPos.y);
    
    

    /// カメラの位置によってクリックの猶予値を変えたい
    if(currentInput.state.left == Started 
      && abs(currentInput.position.x-screenPos.x) <= 20 
      && abs(currentInput.position.y - screenPos.y) <= 20)
    {
        DrawFormatString(0, 220, GetColor(255, 255, 255), "Clicked");
        isConfirm = true;
    }

    /// 確認UIを表示する
    if(isConfirm)
    {
#pragma region UI描画
        Vector2Int crossMinPos = { screenPos.x - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 }; // 左上
        Vector2Int crossMaxPos = { screenPos.x - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 }; // 右下
        Vector2Int checkMinPos = { screenPos.x + CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 };
        Vector2Int checkMaxPos = { screenPos.x + CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 };
        if(isPlaced)
        {
            DrawExtendGraph(crossMinPos.x, crossMinPos.y, crossMaxPos.x, crossMaxPos.y, gHandleCross, FALSE);
        }
        else
        {
            DrawExtendGraph(checkMinPos.x, checkMinPos.y, checkMaxPos.x, checkMaxPos.y, gHandleCheck, FALSE);
        }
#pragma endregion

#pragma region 入力
        if(currentInput.state.left == Started)
        {
            /// 設置するとき
            if(!isPlaced)
            {
                if(currentInput.position.x >= checkMinPos.x && currentInput.position.x <= checkMaxPos.x 
                    && currentInput.position.y >= checkMinPos.y && currentInput.position.y <= checkMaxPos.y)
                {
                    isPlaced = true;
                    isConfirm = false;
                    GameManager::GetInstance().UseItem(TerrainList::CUBE);
                }
                else
                {
                    /// 設置をキャンセル
                    GameManager::GetInstance().RemoveTerrainInfo(pos);
                    mapPtr->RemoveItemPtr(this);
                }
            }

            /// 削除するとき
            else if(oldIsConfirm)
            {
                /// 削除
                if (currentInput.position.x >= crossMinPos.x && currentInput.position.x <= crossMaxPos.x
                    && currentInput.position.y >= crossMinPos.y && currentInput.position.y <= crossMaxPos.y)
                {
                    GameManager::GetInstance().RemoveTerrainInfo(pos);
                    mapPtr->RemoveItemPtr(this);
                }
                /// 削除キャンセル
                else
                {
                    isConfirm = false;
                }
            }
        }

#pragma endregion

    }
    oldIsConfirm = isConfirm;
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
