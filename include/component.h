#pragma once

struct GameObject;
struct GameState;

#include "raylib.h"
#include "types.h"

typedef CompType CompType;

constexpr CompType hashy(const char* str)
{
	CompType h = 0;
	unsigned char* p = nullptr;

	for (p = (unsigned char*)str; *p != '\0'; p++)
		h = 37 * h + *p;
	return h; // or, h % ARRAY_SIZE;
}

const CompType VEHICLE = hashy("VEHICLE");
const CompType RIGIDBODY = hashy("RIGIDBODY");
const CompType POLYRENDERER = hashy("POLYRENDERER");


struct Component
{
	CompType type;
	void (*Init_References)(Component* component, GameObject* gameObject);

	uint16 id;
	uint16 gameObjectId;
	GameObject* gameObject;
};