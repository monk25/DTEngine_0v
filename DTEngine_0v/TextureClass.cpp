#include "pch.h"
#include "TextureClass.h"


TextureClass::TextureClass() : _texture(nullptr)
{
}


TextureClass::~TextureClass()
{
	_texture->Release();
}