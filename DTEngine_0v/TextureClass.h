#pragma once
#include "Define.h"

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	ID3D11ShaderResourceView* _texture;
};

