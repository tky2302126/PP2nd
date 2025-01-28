#pragma once
#include "define.h"
#include "Item.h"
/// <summary>
/// マップに設置する障害物
/// </summary>
class Cube :public Item
{
public:
	Cube();
	~Cube();

	void Init();
	void UnInit();

	void OnEnter() const override;
	void OnExit() const override;

	void Draw() const override;
	void Update() const override;

	void Confirm() const override;

	int& GetMHandle();
private:
	int GHandle;
};

