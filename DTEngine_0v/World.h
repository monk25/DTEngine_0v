#pragma once
#include "Define.h"

class World
{
public:
	World();
	~World();

	void initialize();
	void dispose();

	void render();
	void update(float dt);
	int getKeyState(int vk);
	D3DXVECTOR2 getMousePos();

	bool currentKeys[256];
	bool lastKeys[256];
	POINT mousePos;

	clock_t startClock;
	clock_t currentClock;
	clock_t lastClock;
	double dt;
};

extern World world;
