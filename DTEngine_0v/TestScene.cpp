#include "pch.h"
#include "TestScene.h"


TestScene::TestScene()
{
	spr = new Sprite(L"../Resource/seafloor.dds");
	addChild(spr);
}


TestScene::~TestScene()
{
}

void TestScene::render()
{
	Scene::render();
}

void TestScene::update(float dt)
{
	Scene::update(dt);
}