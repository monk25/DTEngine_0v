#include "pch.h"
#include "SystemClass.h"

#if defined(DEBUG) | defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdling, int iCmdshow)
#endif
{
	SystemClass* System;
	bool result;

	System = new SystemClass;
	if (!System) {
		return 0;
	}
	cout << "Â¥¸´ÇØ~" << endl;
	System->Run();

	delete System;

	return 0;
}