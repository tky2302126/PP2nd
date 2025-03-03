#include "Decoy.h"
#include "Map.h"

Decoy::Decoy()
	:MHandle(-1),
	pos(VECTOR()),
	mapPtr(nullptr),
    oldIsConfirm (false)
{
}

Decoy::~Decoy()
{
}

void Decoy::Init(int _Mhandle, VECTOR _pos, Map* _mapPtr)
{
	MHandle = _Mhandle;
	pos = _pos;
	mapPtr = _mapPtr;
}

void Decoy::UnInit()
{
}

void Decoy::Draw() const
{
	MV1SetPosition(MHandle, pos);
	MV1DrawModel(MHandle);
}

void Decoy::Update()
{
    /// カメラの描画範囲なら実行
    Draw();

    /// クリックされたら確認UIを表示
    auto currentInput = Input().GetMouseInfo();

    Vector2Int screenPos = GetScreenPos(pos);

    /// カメラの位置によってクリックの猶予値を変えたい
    if (currentInput.state.left == Started
        && abs(currentInput.position.x - screenPos.x) <= 20
        && abs(currentInput.position.y - screenPos.y) <= 20)
    {
        DrawFormatString(0, 220, GetColor(255, 255, 255), "Clicked");
        isConfirm = true;
    }

    /// 確認UIを表示する
    if (isConfirm)
    {
#pragma region UI描画
        Vector2Int crossMinPos = { screenPos.x - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 }; // 左上
        Vector2Int crossMaxPos = { screenPos.x - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 }; // 右下
        Vector2Int checkMinPos = { screenPos.x + CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET - CONFIRM_PANEL_SIZE / 2 };
        Vector2Int checkMaxPos = { screenPos.x + CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 , screenPos.y - CONFIRM_PANEL_OFFSET + CONFIRM_PANEL_SIZE / 2 };
        if (isPlaced)
        {
            DrawExtendGraph(crossMinPos.x, crossMinPos.y, crossMaxPos.x, crossMaxPos.y, gHandleCross, FALSE);
        }
        else
        {
            DrawExtendGraph(checkMinPos.x, checkMinPos.y, checkMaxPos.x, checkMaxPos.y, gHandleCheck, FALSE);
        }
#pragma endregion

#pragma region 入力
        if (currentInput.state.left == Started)
        {
            /// 設置するとき
            if (!isPlaced)
            {
                if (CheckInRect(currentInput.position, checkMinPos, checkMaxPos))
                {
                    isPlaced = true;
                    isConfirm = false;
                    GM().UseItem(TerrainList::CUBE);
                    TM().ChangeGameSpeedSlower(false);
                    AM().PlaySE(SEList::LOWBON);
                }
                else
                {
                    /// 設置をキャンセル
                    GM().RemoveTerrainInfo(pos);
                    mapPtr->RemoveItemPtr(this);
                    TM().ChangeGameSpeedSlower(false);
                }
            }

            /// 削除するとき
            else if (oldIsConfirm)
            {
                /// 削除
                if (CheckInRect(currentInput.position, crossMinPos, crossMaxPos))
                {
                    GM().RemoveTerrainInfo(pos);
                    TM().ChangeGameSpeedSlower(false);
                    mapPtr->RemoveItemPtr(this);
                }
                /// 削除キャンセル
                else
                {
                    TM().ChangeGameSpeedSlower(false);
                    isConfirm = false;
                }
            }
        }

#pragma endregion

    }
    oldIsConfirm = isConfirm;
}

void Decoy::Confirm()
{
    /// カメラの中央付近に来るようにカメラを動かす(優先順位:低)
    /// 自分のPosを渡し、ｘを一致、ｚをCameraOFFSET分離す

    isConfirm = true;
    TM().ChangeGameSpeedSlower(true);

    /// 試しに置いて進行ルートが閉鎖されないか確認

    /// いったん登録のみ
    if (!isPlaced)
        GM().AddTerrainInfo(TerrainList::DECOY, pos);
}

int& Decoy::GetMHandle() const
{
    int MHandle = -1;
    return MHandle;
}
