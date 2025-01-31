#pragma once
#include "define.h"
#include "Item.h"
#include "manager.h"
/// <summary>
/// マップに設置する障害物
/// </summary>
class Cube :public Item
{
public:
	Cube();
	~Cube();

	void Init();
	void Init(int Ghandle) override;
	void Init(int Ghandle,VECTOR pos) override;

	void UnInit();

	void OnEnter() const override;
	void OnExit() const override;
	void Draw() const override;
	void Update() const override;
	void Confirm() override;

	int& GetMHandle() const override;
private:
	int MHandle;
	VECTOR pos;
	bool isConfirm = false;
	
};

