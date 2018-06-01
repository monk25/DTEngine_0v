#include "pch.h"
#include "SystemClass.h"
#include "World.h"


SystemClass::SystemClass() : worldRotation(0.0f, 0.0f, 0.0f)
{
	int screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;

	initializeWindows(screenWidth, screenHeight);
	world.initialize();
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
	world.dispose();
	shutdownWindows();
}

void SystemClass::run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			result = frame();
			if (!result) {
				MessageBox(_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
		}
	}
}

bool SystemClass::frame()
{
	bool result;

	return true;
}

void SystemClass::initializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	applicationHandle = this;
	_hinstance = GetModuleHandle(NULL);
	_applicationName = L"Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN) {
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = screenWidth;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else {
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	_hwnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY,
		screenWidth, screenHeight, NULL, NULL, _hinstance, NULL);

	ShowWindow(_hwnd, SW_SHOW);
	SetForegroundWindow(_hwnd);
	SetFocus(_hwnd);

	ShowCursor(false);

	return;
}

void SystemClass::shutdownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(_hwnd);
	_hwnd = NULL;

	UnregisterClass(_applicationName, _hinstance);
	_hinstance = NULL;

	applicationHandle = NULL;

	return;
}

LRESULT CALLBACK SystemClass::MessageHandle(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		return applicationHandle->MessageHandle(hwnd, umsg, wparam, lparam);
	}
}