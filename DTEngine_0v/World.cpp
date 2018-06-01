#include "pch.h"
#include "World.h"
#include "Asset.h"
#include "SystemClass.h"


World::World()
{
}


World::~World()
{
}


void World::initialize()
{
	asset.initialize();
	cout.precision(3);
	ZeroMemory(currentKeys, sizeof(currentKeys));
	ZeroMemory(lastKeys, sizeof(lastKeys));
	startClock = clock();
	currentClock = clock();
	lastClock = clock();
}

void World::dispose()
{
	asset.dispose();
}

void World::render()
{

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