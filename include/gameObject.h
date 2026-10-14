#pragma once

struct RigidBody;
struct Component;

#include "raylib.h"
#include "render.h"


struct GameObject
{
	uint16 id;
	Transform transform;

	Component* components[5] = {};
	uint16 componentsCount = 0;

	RigidBody* rigidbody;
	uint16 rigidbodyid;

	PolyRenderer* shape;
	uint16 renderId;
};

struct GameObjectForm
{
	uint16 size;
	ComponentForm firstComponent;
};


GameObject GameObjectCreate();

void AddComponent();