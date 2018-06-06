#include "pch.h"
#include "Sprite.h"
#include "Asset.h"
#include "World.h"


Sprite::Sprite() : color(1, 1, 1, 1), texture(nullptr)
{
}

Sprite::Sprite(wstring path) : color(1, 1, 1, 1), texture(nullptr)
{
	setPath(path);
}

Sprite::Sprite(const Sprite& other)
{
}

Sprite::~Sprite()
{
}

void Sprite::setPath(wstring path)
{
	texture = asset.getTexture(path);
}

void Sprite::render()
{
	if (!visible || texture == nullptr) return;
	Entity::render();


}