#include "TestEnemy.h"
#include "Start.h"
#include "manager.h"
#include "Cube.h"

TestEnemy::TestEnemy()
{
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Init(int _Mhandle =-1)
{
}

void TestEnemy::Init(int, Start* _start = nullptr)
{
	myStart = _start;
    auto mapInfo = GameManager::GetInstance().GetMapInfo();
    /// ヒューリスティック値から体力を設定する
    /// ->Startで計算した方がよさそう
    if(myStart!=nullptr)
    {
        health = currentHealth = myStart->BaseHealth();
    }
    else
    {
        health = currentHealth = 600;
    }
    InGaugeGH = LoadGraph("./Resource/GaugeIn306x27_HP.png");
    OutGaugeGH = LoadGraph("./Resource/GaugeOut306x27_002.png");
}

void TestEnemy::Draw() const
{
	float height = 50.0f;
    int color = GetColor(255, 255, 255);
    if (attack) { color = GetColor(255, 128, 128); }
	DrawCapsule3D(VGet(position.x, position.y + height, position.z), 
		VGet(position.x, position.y, position.z), 
		50.0f, 
		32,
		color,
		color,
		TRUE);

    auto screenPos = GetScreenPos(position);

    float healthRate = (float)currentHealth / health;

    Vector2Int start = { screenPos.x - ENEMY_GAUGE_WIDTH/2, screenPos.y - ENEMY_GAUGE_HEIGHT - ENEMY_GAUGE_OFFSET_Y };
    Vector2Int end = { start.x + ENEMY_GAUGE_WIDTH, start.y + ENEMY_GAUGE_HEIGHT };
    Vector2Int inEnd = { start.x + (ENEMY_GAUGE_WIDTH * healthRate) , start.y + ENEMY_GAUGE_HEIGHT };

    DrawExtendGraph(start.x, start.y, end.x,end.y, OutGaugeGH,FALSE);
    DrawExtendGraph(start.x, start.y, inEnd.x,inEnd.y,InGaugeGH,FALSE);
}

void TestEnemy::Move()
{
    /// 基底クラスで定義する
    
	/// 自身のposをrouteを参考に動かす
	/// !pathFoundがtrueでない時はtempRouteで計算
	/// myroute[0]->[1]へ移動する
    if(move)
    {
	    if(myRoute.size()>=2)
	    {
	    	VECTOR start = ArrayPos2WorldPosCenter(myRoute[0].x, myRoute[0].y);
	    	VECTOR end = ArrayPos2WorldPosCenter(myRoute[1].x, myRoute[1].y);
	    	VECTOR moveVec = VSub(end, position);
	    	moveVec = VNorm(moveVec);
            if (TimeManager::GetInstance().IsFast()) { moveVec = VScale(moveVec, GAMESPEED_FASTRATE); }
            if (TimeManager::GetInstance().IsSlow()) { moveVec = VScale(moveVec, GAMESPEED_SLOWRATE); }
	    	moveVec = VScale(moveVec, ENEMY_MOVE_SPEED);
            auto moveDuration = VSize(moveVec);
            currentHealth -= moveDuration;
	    	position = VAdd(position, moveVec);
	    	float distance = sqrt(pow(position.x-end.x, 2) + pow(position.z-end.z, 2));
	    	if(distance <= ENEMY_MOVE_SPEED)
	    	{
	    		myRoute.erase(myRoute.begin());
	    	}
	    }

        Vector2Int currentArrayPos = WorldPos2ArrayPos(position);
        /// OnEnterEventの実行
        auto terrainInfo = GameManager::GetInstance().GetTerrainInfo();
        auto mapInfo = GameManager::GetInstance().GetMapInfo();
        if (!IsValidPosition(currentArrayPos, mapInfo)) return;
        switch (terrainInfo[currentArrayPos.y][currentArrayPos.x])
        {
        case TerrainList::Goal:
            GameManager::GetInstance().GameOver();
            /// 自身を破棄
            break;
        case TerrainList::Base:
            /// 破壊する

        case TerrainList::CUBE:
            /// 破壊する
            move = false;
            attack = true;
            attackBeginTime = GetNowCount();
            /// ここに処理を追加

            break;

        default:
            break;
        }

    }

    Vector2Int currentArrayPos = WorldPos2ArrayPos(position);
    /// マスの位置が更新されたとき、イベントを実行する (基底クラスで実装)
    if(oldPos != currentArrayPos)
    {
        auto terrainInfo = GameManager::GetInstance().GetTerrainInfo();
        auto mapInfo = GameManager::GetInstance().GetMapInfo();
        /// OnExitEventの実行
        
        if (IsValidPosition(oldPos, mapInfo)) 
        {
            switch (terrainInfo[oldPos.y][oldPos.x])
            {
                /// ここに処理を追加


            default:
                break;
            }
        }
        
        
        oldPos = currentArrayPos;
    }
}

/// <summary>
/// 攻撃のアニメーションを実行する
/// 終了したらmoveに戻る
/// </summary>
void TestEnemy::Attack()
{
    int currentTime = GetNowCount();
    if(currentTime - attackBeginTime >= ENEMY_ATTACK_TIME * 1000)
    {
        attack = false;
        move = true;
        GameManager::GetInstance().RemoveTerrainInfo(this->position);
    }
}

void TestEnemy::Update()
{
    if(currentHealth <=0)
    {
        /// 死亡処理
        EnemyManager::GetInstance().RemoveEnemy(this);
        return;
    }
	Move();
	Draw();
    if (attack) { Attack(); }
}

void TestEnemy::SetRoute(std::vector<Vector2Int> _route)
{
	myRoute = _route;
	position = ArrayPos2WorldPosCenter(myRoute[0].x, myRoute[0].y);
}

/// <summary>

/// </summary>
/// <param name="_route"></param>
void TestEnemy::CompareRoute(std::vector<Vector2Int> _route)
{
	auto route = _route;
	while (true)
	{
		/// なかった場合、ルートを再設定する
		if(route.empty())
		{
			RecalculateRoute();
			break;
		}
		/// スポーン地点からの進行ルートと自分のルートを比較する
		if(route.front() == myRoute.front())
		{
			/// 新しい進行ルートに自分のルート内の座標があった場合、
			myRoute.clear();
			myRoute = route; /// その地点から置き換える
			break;
		}
		else
		{
			route.erase(route.begin());
		}
	}
}

/// <summary>
/// ルートの再設定
/// </summary>
/// <param name="_route"></param>
void TestEnemy::RecalculateRoute()
{
    /// ルートが設定されていた場合、再計算が必要か計算する
    /// 変更箇所のみ再計算する 現行1マスずつ変更が行われるため、
    /// 障害物が除かれた場合は再計算の必要がある

    const std::vector<Vector2Int> directions = { {0, 1},{1, 0},{0,-1},{-1, 0} };
    /// 配列座標へ変換
    Vector2Int goal =
    {
        GameManager::GetInstance().GetMapInfo().goalWidth - 1,
        GameManager::GetInstance().GetMapInfo().goalHeight - 1
    };
    ///
    auto map = GameManager::GetInstance().GetMapInfo();
    auto terrainInfo = GameManager::GetInstance().GetTerrainInfo();
    std::priority_queue<Node*, std::vector<Node*>, Compare> openList; /// 探索予定エリア
    std::unordered_set<Vector2Int, Hash> closedSet; ///探索済みエリア
    unmap<Vector2Int, Node*, Hash> nodeMap; // ノード管理
    Vector2Int startPos = { myRoute.front().x -1, myRoute.front().y -1};
    Node* start = new Node(startPos, 0, GetHeuristic(startPos, goal));

    openList.push(start);
    nodeMap[startPos] = start;

    while (!openList.empty())
    {
        Node* current = openList.top();
        openList.pop();

        if (current->pos == goal)
        {

            myRoute.clear();

            while (current)
            {
                myRoute.push_back(current->pos);
                current = current->parent;
            }
            reverse(myRoute.begin(), myRoute.end());
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
            if (neighborPos.x >= 0 && neighborPos.y >= 0
                && neighborPos.x < terrainInfo[0].size() && neighborPos.y < terrainInfo.size())
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
            if (nodeMap.count(neighborPos) && nodeMap[neighborPos]->cost <= cost)
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
