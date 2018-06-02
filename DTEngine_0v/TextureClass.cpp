#include "pch.h"
#include "TextureClass.h"


TextureClass::TextureClass() : _texture(nullptr)
{
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
	_texture->Release();
}