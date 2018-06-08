#include "pch.h"
#include "Scene.h"

Scene::Scene() : followTarget(nullptr), _camera
(nullptr)
{
	_camera = new CameraClass();
}

Scene::Scene(const Scene& other)
{
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
	Entity::update(dt);

	D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 0);

	if (followTarget) {
		targetPos = -followTarget->center();
	}

	D3DXVECTOR2 p = (targetPos + offset - D3DXVECTOR2(_camera->_positionX, _camera->_positionY)) * 0.15;
	_camera->_positionX += p.x;
	_camera->_positionY += p.y;
}

void Scene::follow(Entity* target, D3DXVECTOR2 offset)
{
	followTarget = target;
	this->offset = offset;
}

void Scene::unfollow()
{
	followTarget = nullptr;
	offset = D3DXVECTOR2(0.0f, 0.0f);
}

void Scene::shake(int cnt, float range, float duration)
{
	shakeTimer.reset(duration, cnt);
	shakeTimer.onTick = [=]() {
		//_camera->_positionX += random(-range, range);
		//_camera->_positionY += random(-range, range);
	};
}