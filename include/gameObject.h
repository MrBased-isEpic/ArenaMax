#pragma once

struct RigidBody;
struct PolyRenderer;

#include "component.h"
#include "raylib.h"
#include "arrays.h"


struct GameObject
{
	char name[64];
	uint16 id;
	Transform transform;

	Component* components[5] = {};
	uint16 componentsCount = 0;
};

void GameObject_SetComponentReference(
	GameObject* gameObject,
	Component* newAddress);

void GameObject_RemoveComponentReference(
	GameObject* gameObject,
	Component* component);