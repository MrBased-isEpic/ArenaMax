#pragma once

struct RigidBody;
struct PolyRenderer;

#include "component.h"
#include "raylib.h"


struct GameObject
{
	uint16 id;
	Transform transform;

	Component* components[5] = {};
	uint16 componentsCount = 0;

	PolyRenderer* shape;
	uint16 renderId;
};

void GameObject_SetComponentReference(
	GameObject* gameObject,
	CompType type,
	Component* newAddress);