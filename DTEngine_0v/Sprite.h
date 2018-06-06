#pragma once
#include "Entity.h"
#include "TextureClass.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(wstring path);
	Sprite(const Sprite& other);
	virtual ~Sprite();

	void setPath(wstring path);
	void render();

	TextureClass* texture;
	D3DXCOLOR color;
};

