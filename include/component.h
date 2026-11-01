#pragma once

struct GameObject;
struct GameState;

#include "types.h"

enum CompType
{
	NONE,
	VEHICLE,
	RIGIDBODY,
	POLYRENDERER
};

struct Component
{
	CompType type;
	void (*Init_References)(Component* component, GameObject* gameObject);

	uint16 id;
	uint16 gameObjectId;
	GameObject* gameObject;
};