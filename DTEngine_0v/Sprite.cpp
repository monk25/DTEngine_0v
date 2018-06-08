#include "pch.h"
#include "Sprite.h"
#include "World.h"


Sprite::Sprite() : color(1, 1, 1, 1), bitmap(nullptr)
{
}

Sprite::Sprite(wstring path) : color(1, 1, 1, 1), bitmap(nullptr)
{
	setPath(path);
}

Sprite::Sprite(const Sprite& other)
{
}

Sprite::~Sprite()
{
	if (bitmap) {
		delete bitmap;
	}
}

void Sprite::setPath(wstring path)
{
	bitmap = new BitmapClass(world._d3d->_device, 1280, 720, const_cast<WCHAR*>(path.c_str()), 100, 100);
}

void Sprite::render()
{
	if (!visible || bitmap == nullptr) return;
	Entity::render();

	bitmap->render(world._d3d->_deviceContext, pos.x, pos.y);
	world._textureShader->render(world._d3d->_deviceContext, bitmap->getIndexCount(),
		world._d3d->_worldMatrix, world.currentScene->_camera->_viewMatrix, world._d3d->_orthoMatrix, bitmap->_texture->_texture);
}