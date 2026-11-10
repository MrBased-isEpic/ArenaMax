#pragma once

struct RigidBody;
struct PolyRenderer;

#include "component.h"
#include "raylib.h"

//struct ComponentRefList
//{
//	SwapBackArray list;
//
//};

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
	Component* newAddress);

void GameObject_RemoveComponentReference(
	GameObject* gameObject,
	Component* component);