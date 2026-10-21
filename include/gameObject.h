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

	RigidBody* rigidbody;
	uint16 rigidbodyid;

	PolyRenderer* shape;
	uint16 renderId;
};