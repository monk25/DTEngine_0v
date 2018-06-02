#pragma once
#include "Define.h"
#include "D3DClass.h"

class TextureShaderClass;
class LightShaderClass;

class World
{
public:
	World();
	~World();

	void initialize(int screenWidth, int screenHeight);
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

	D3DClass* _d3d;
	TextureShaderClass* _textureShader;
};

extern World world;

