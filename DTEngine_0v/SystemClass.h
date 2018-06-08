#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Define.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	void run();

	LRESULT CALLBACK MessageHandle(HWND, UINT, WPARAM, LPARAM);

private:
	bool frame();
	void initializeWindows(int&, int&);
	void shutdownWindows();

public:
	HWND _hwnd;

	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLE = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

private:
	LPCWSTR _applicationName;
	HINSTANCE _hinstance;
	D3DXVECTOR3 worldRotation;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* applicationHandle = nullptr;