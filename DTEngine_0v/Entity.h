#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	Entity(const Entity&);
	virtual ~Entity();

	virtual void update(float dt);
	virtual void render();
	void addChild(Entity* child);
	static void removeChild(Entity* child);
	Rect rectWithPos();
	void setCenter(D3DXVECTOR2 pos);
	D3DXVECTOR2 center();

	Entity* parent;
	vector<Entity*> children;
	D3DXVECTOR2 pos;
	float rotation;
	D3DXVECTOR2 rotationCenter;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 scaleCenter;
	D3DXMATRIX matrix;
	Rect rect;
	Rect visibleRect;
	bool visible;
	bool updateEnabled;
	bool renderChildrenEnabled;
	bool removing;
};

