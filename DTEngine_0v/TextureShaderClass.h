#pragma once
#include "Define.h"

class TextureShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	TextureShaderClass(ID3D11Device*, HWND);
	TextureShaderClass(const TextureShaderClass&);
	~TextureShaderClass();

	bool render();
};

