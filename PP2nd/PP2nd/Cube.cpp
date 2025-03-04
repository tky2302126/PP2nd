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
    auto currentInput = Input().GetMouseInfo();

    Vector2Int screenPos = GetScreenPos(pos); 

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
                if(CheckInRect(currentInput.position, checkMinPos, checkMaxPos))
                {
                    isPlaced = true;
                    isConfirm = false;
                    GameM().UseItem(TerrainList::CUBE);
                    TimeM().ChangeGameSpeedSlower(false);
                    AudioM().PlaySE(SEList::LOWBON);
                }
                else
                {
                    /// 設置をキャンセル
                    GameM().RemoveTerrainInfo(pos);
                    mapPtr->RemoveItemPtr(this);
                    TimeM().ChangeGameSpeedSlower(false);
                }
            }

            /// 削除するとき
            else if(oldIsConfirm)
            {
                /// 削除
                if (CheckInRect(currentInput.position, crossMinPos, crossMaxPos))
                {
                    GameM().RemoveTerrainInfo(pos);
                    TimeM().ChangeGameSpeedSlower(false);
                    mapPtr->RemoveItemPtr(this);
                }
                /// 削除キャンセル
                else
                {
                    TimeM().ChangeGameSpeedSlower(false);
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
    TimeM().ChangeGameSpeedSlower(true);

    /// 試しに置いて進行ルートが閉鎖されないか確認

    /// いったん登録のみ
    if(!isPlaced)
        GameM().AddTerrainInfo(TerrainList::CUBE, pos);
}

int& Cube::GetMHandle() const
{
    int MHandle = -1;
    return MHandle;
}
