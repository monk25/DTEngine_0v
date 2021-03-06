#include "pch.h"
#include "World.h"
#include "Asset.h"
#include "Timer.h"
#include "SystemClass.h"
#include "TextureShaderClass.h"


World::World() : _d3d(nullptr), _textureShader(nullptr), currentScene(nullptr)
{
}


World::~World()
{
}


void World::initialize(int screenWidth, int screenHeight)
{
	asset.initialize();
	cout.precision(3);
	ZeroMemory(currentKeys, sizeof(currentKeys));
	ZeroMemory(lastKeys, sizeof(lastKeys));
	startClock = clock();
	currentClock = clock();
	lastClock = clock();
	_d3d = new D3DClass(screenWidth, screenHeight, applicationHandle->_hwnd);
	_textureShader = new TextureShaderClass(_d3d->_device, applicationHandle->_hwnd);
}

void World::dispose()
{
	asset.dispose();
}

void World::render()
{
	if (!currentScene) return;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	_d3d->begineScene(0.0f, 0.0f, 0.0f, 1.0f);

	currentScene->_camera->render();

	viewMatrix = currentScene->_camera->_viewMatrix;
	worldMatrix = _d3d->_worldMatrix;
	projectionMatrix = _d3d->_projectionMatrix;
	orthoMatrix = _d3d->_orthoMatrix;

	_d3d->turnZBufferOff();
	currentScene->render();
	_d3d->turnZBufferOn();
	_d3d->endScene();
}

void World::update(float dt)
{
	lastClock = currentClock;
	currentClock = clock();
	dt = (double)(currentClock - lastClock) / CLOCKS_PER_SEC;

	for (int i = 0; i < 256; i++) {
		lastKeys[i] = currentKeys[i];
		currentKeys[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mousePos);
	ScreenToClient(applicationHandle->_hwnd, &mousePos);

	for (auto* timer : timers)
		timer->update(dt);

	if (currentScene) currentScene->update(dt);
}

void World::changeScene(Scene* scene)
{
	if (currentScene) delete currentScene;
	currentScene = scene;
}

int World::getKeyState(int vk)
{
	if (currentKeys[vk] && lastKeys[vk]) return 2;
	if (currentKeys[vk] && !lastKeys[vk]) return 1;
	if (!currentKeys[vk] && lastKeys[vk]) return -1;
	return -2;
}

D3DXVECTOR2 World::getMousePos()
{
	return D3DXVECTOR2(mousePos.x, mousePos.y);
}

World world;