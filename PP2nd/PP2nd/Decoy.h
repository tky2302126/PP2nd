#pragma once
#include "define.h"
#include "Item.h"
#include "manager.h"

class Map;

class Decoy :public Item
{
public:
	Decoy();
	~Decoy();

	void Init();
	void Init(int Ghandle) override;
	void Init(int Ghandle, VECTOR pos) override;
	void Init(int Ghandle, VECTOR pos, Map* mapPtr) override;

	void UnInit();

	void OnEnter() const override;
	void OnExit() const override;
	void Draw() const override;
	void Update() override;
	void Confirm() override;

	int& GetMHandle() const override;
	VECTOR GetPosition() const override { return pos; };

private:
	int MHandle;
	VECTOR pos;
	bool isConfirm = false;
	bool oldIsConfirm;
	bool isPlaced = false;
	Map* mapPtr;
};

