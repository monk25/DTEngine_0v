#include "pch.h"
#include "Entity.h"


Entity::Entity() :
	pos(0, 0),
	rotation(0.0f),
	rotationCenter(0, 0),
	scale(1, 1),
	scaleCenter(0, 0),
	rect(0, 0, 0, 0),
	visibleRect(0, 0, 0, 0),
	visible(true),
	updateEnabled(true),
	renderChildrenEnabled(true),
	removing(false),
	parent(nullptr)
{
}

Entity::Entity(const Entity& other)
{
}

Entity::~Entity()
{
	for (auto* child : children)
		delete child;
}

void Entity::addChild(Entity* child)
{
	child->parent = this;
	children.push_back(child);
}

void Entity::removeChild(Entity* child)
{
	child->removing = true;
}

void Entity::update(float dt)
{
	if (!updateEnabled) return;

	for (auto* child : children)
		child->update(dt);

	children.erase(remove_if(children.begin(), children.end(), [](Entity* child) {
		if (child->removing) {
			delete child;
			return true;
		}
		return false;
	}), children.end());
}

void Entity::render()
{
	if (!visible) return;
	D3DXMatrixTransformation2D(&matrix, &scaleCenter, 0, &scale, &rotationCenter, rotation, &pos);

	if (parent)
		matrix *= parent->matrix;

	if (!renderChildrenEnabled) return;
	for (auto* child : children)
		child->render();
}

D3DXVECTOR2 Entity::center()
{
	return pos + rect.center();
}

Rect Entity::rectWithPos()
{
	return rect.offset(pos);
}