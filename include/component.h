#pragma once

struct GameObject;
struct GameState;

#include "raylib.h"
#include "types.h"

constexpr uint32 hashy(const char* str)
{
	uint32 h = 0;
	unsigned char* p = nullptr;

	for (p = (unsigned char*)str; *p != '\0'; p++)
		h = 37 * h + *p;
	return h; // or, h % ARRAY_SIZE;
}

const uint32 VEHICLE = hashy("VEHICLE");
const uint32 RIGIDBODY = hashy("RIGIDBODY");
const uint32 POLYRENDERER = hashy("POLYRENDERER");


struct Component
{
	uint32 type;
	void (*Init_References)(Component* component, GameObject* gameObject);

	uint16 id;
	uint16 gameObjectId;
	GameObject* gameObject;
};