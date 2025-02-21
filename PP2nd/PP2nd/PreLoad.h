#pragma once
#include "define.h"
#include "Scene.h"
class PreLoad :public Scene
{
public:
	PreLoad();
	~PreLoad();
	void Init();
	void UnInit();
	void Load(SceneName, SceneName);
	void Release(SceneName);
	void Update() const override;
private:
	std::thread model;
	std::thread sound;
	std::thread image;
};

