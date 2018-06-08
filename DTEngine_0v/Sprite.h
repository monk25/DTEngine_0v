#pragma once
#include "Entity.h"
#include "BitmapClass.h"

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

	BitmapClass* bitmap;
	D3DXCOLOR color;
};

