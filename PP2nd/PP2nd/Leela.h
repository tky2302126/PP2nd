#pragma once
#include "define.h"
#include "Enemy.h"
#include "Animator.h"

class Start;

enum LeelaAnimList
{
	Dance,
	Death,
	Hello,
	HitRecieve_1,
	HitRecieve_2,
	Idle,
	Jump,
	Kick,
	No_Count,
	PickUp,
	Punch,
	Run,
	Run_Tall,
	Shoot,
	SwordSlash,
	Walk,
	Walk_Tall,
	Yes,
	Leela_ALL,
};

class Leela :public Enemy
{
public:
	Leela();
	~Leela();
	void Init(int) override;
	void Init(int Mhandle, Start*) override;
	void Draw() const override;
	void Move() override;
	void Attack();
	void Update() override;
	void SetRoute(std::vector<Vector2Int> _route) override;
	void CompareRoute(std::vector<Vector2Int> _route) override;
	void RecalculateRoute() override;
	Start* GetMyStart() const override { return myStart; }
private:
	UniquePtr<Animator> animUPtr;
	int mHandle;
	int attackPower = 100;
	float rotation;
	bool isDead = false;
};

