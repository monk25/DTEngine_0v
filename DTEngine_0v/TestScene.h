#pragma once
#include "Scene.h"
#include "Sprite.h"

class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	void render();
	void update(float dt);

	Sprite* spr;
};

