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
    /// ルートが設定されていた場合、再計算が必要か計算する
    /// 変更箇所のみ再計算する 現行1マスずつ変更が行われるため、
    /// 障害物が除かれた場合は再計算の必要がある

    const vector<Vector2Int> directions = { {0, 1},{1, 0},{0,-1},{-1, 0} };
    /// 配列座標へ変換
    Vector2Int goal =
    {
        GameManager::GetInstance().GetMapInfo().goalWidth-1,
        GameManager::GetInstance().GetMapInfo().goalHeight-1
    };
    ///
    auto map = GameManager::GetInstance().GetMapInfo();
    auto terrainInfo = GameManager::GetInstance().GetTerrainInfo();
    priority_queue<Node*, vector<Node*>, Compare> openList; /// 探索予定エリア
    unordered_set<Vector2Int, Hash> closedSet; ///探索済みエリア
    unmap<Vector2Int, Node*, Hash> nodeMap; // ノード管理
    Vector2Int startPos = { pos.x - 1,pos.y - 1 };
    Node* start = new Node(startPos, 0, GetHeuristic(pos, goal));

    openList.push(start);
    nodeMap[startPos] = start;

    while (!openList.empty())
    {
        Node* current = openList.top();
        openList.pop();

        if (current->pos == goal)
        {

            route.clear();

            while (current)
            {
                route.push_back(current->pos);
                current = current->parent;
            }
            reverse(route.begin(), route.end());
            break;
        }

        closedSet.insert(current->pos);

        for (const auto& dir : directions)
        {
            Vector2Int neighborPos = { current->pos.x + dir.x, current->pos.y + dir.y };
            if (!IsValidPosition(neighborPos, map) || closedSet.count(neighborPos))
            {
                continue;
            }
            int cost = current->cost + 1;
            /// 地形情報の値を参照
            ///! 領域外を検索するリスクを回避
            auto terrain = TerrainList::None;
            if(neighborPos.x>=0 && neighborPos.y >= 0
               && neighborPos.x<terrainInfo[0].size()&& neighborPos.y <terrainInfo.size())
            {
                terrain = terrainInfo[neighborPos.y][neighborPos.x];
            }
            switch (terrain)
            {
            case TerrainList::CUBE:
                cost += 99;
                break;
            case TerrainList::ItemAll:
                break;
            case TerrainList::Invailed:
                break;
            case TerrainList::Polluted:
                cost += 99;
                break;

                /// 地形を増やしたときに処理を追加
            default:
                break;
            }

            /// より優れた経路があるときスキップ
            if (nodeMap.count(neighborPos)&& nodeMap[neighborPos]->cost <= cost)
            {
                continue;
            }

            Node* neighbor = new Node(neighborPos, cost, GetHeuristic(neighborPos, goal), current);
            openList.push(neighbor);
            nodeMap[neighborPos] = neighbor;
        }
    }
    for (auto& [_, node] : nodeMap) { delete node; }
    /// 見つからなかった場合の処理
}

bool Start::ReachGoal()
{
    return false;
}

void Start::DrawRouteTest()
{
    if (route.empty()) return;
    for(int i=0;i<route.size()-1;i++)
    {
        DrawLine3D(VGet(route[i].x*MAP_UNIT+MAP_UNIT/2,0,route[i].y*MAP_UNIT+MAP_UNIT/2), VGet(route[i+1].x * MAP_UNIT + MAP_UNIT / 2, 0, route[i+1].y * MAP_UNIT + MAP_UNIT / 2), GetColor(255, 64, 64));
    }
}


