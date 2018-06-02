#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "Define.h"

class D3DClass
{
public:
	D3DClass(int, int, HWND);
	D3DClass(const D3DClass&);
	~D3DClass();

	void begineScene(float, float, float, float);
	void endScene();

	void turnZBufferOn();
	void turnZBufferOff();

private:
	bool _vsync_enabled;
	int _videoCardMemory;
	char _videoCardDescription[128];
	IDXGISwapChain* _swapChain;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilState* _depthStencilState;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11RasterizerState* _rasterState;
	ID3D11DepthStencilState* _depthDisabledStencilState;

public:
	ID3D11Device * _device;
	ID3D11DeviceContext* _deviceContext;
	D3DXMATRIX _projectionMatrix;
	D3DXMATRIX _worldMatrix;
	D3DXMATRIX _orthoMatrix;
};