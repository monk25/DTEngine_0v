#pragma once
#include "Entity.h"
#include "Timer.h"
#include "CameraClass.h"

class Scene :
	public Entity
{
public:
	Scene();
	Scene(const Scene&);
	~Scene();

	void update(float dt);
	void follow(Entity* target, D3DXVECTOR2 offset);
	void unfollow();
	void shake(int cnt, float range, float duration);

	Entity* followTarget;
	D3DXVECTOR2 offset;
	Timer shakeTimer;

	CameraClass* _camera;
};

