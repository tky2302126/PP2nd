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
    const vector<Vector2Int> directions = { {0, 1},{1, 0},{0,-1},{-1, 0} };
    Vector2Int goal =
    {
        GameManager::GetInstance().GetMapInfo().goalWidth,
        GameManager::GetInstance().GetMapInfo().goalHeight
    };
    ///
    _mapInfo map = GameManager::GetInstance().GetMapInfo();
    priority_queue<Node*, vector<Node*>, Compare> openList; /// 探索予定エリア
    unordered_set<Vector2Int, Hash> closedSet; ///探索済みエリア

    Node* start = new Node(pos, 0, GetHeuristic(pos, goal));

    openList.push(start);

    while (!openList.empty())
    {
        Node* current = openList.top();
        openList.pop();

        if(current->pos == goal)
        {
            while (current)
            {
                route.push_back(current->pos);
                current = current->parent;
            }
            reverse(route.begin(), route.end());
            break;
        }

        closedSet.insert(current->pos);

        for(const auto& dir : directions)
        {
            Vector2Int neighborPos = { current->pos.x + dir.x, current->pos.y + dir.y };
            if(!IsValidPosition(neighborPos,map)|| closedSet.count(neighborPos))
            {
                continue;
            }
            /// ! 地形情報の値を参照予定
            int cost = current->cost + 1;
            Node* neighbor = new Node(neighborPos, cost, GetHeuristic(neighborPos, goal), current);
            openList.push(neighbor);
        }
    }

    /// 見つからなかった場合の処理
}

bool Start::ReachGoal()
{
    return false;
}


