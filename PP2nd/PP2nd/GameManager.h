#pragma once
#include "define.h"
#include "Item.h"
/// <summary>
/// ���C�����[�v�̐i�s���Ǘ�
/// �K�v�ȃf�[�^��ێ��A�󂯓n���̖�����z��
/// </summary>

enum ItemList
{
	Cube,
	ALL
};

struct HandleData
{
	int GHandle;
	int MHandle;
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Load();
	void Init();
	void UnInit();

	static GameManager& GetInstance();

private:

	vector<HandleData> handleInfo;

	static UniquePtr<GameManager> Instance;
};

