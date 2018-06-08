#include "pch.h"
#include "SystemClass.h"
#include "World.h"

#if defined(DEBUG) | defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdling, int iCmdshow)
#endif
{
	SystemClass* System;
	bool result;

	System = new SystemClass();
	world.initialize(800, 600);
	if (!System) {
		return 0;
	}

	System->run();

	delete System;

	return 0;
}