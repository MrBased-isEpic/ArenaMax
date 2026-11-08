#pragma once

struct GameObject;
struct GameState;

#include "raylib.h"
#include "types.h"

constexpr uint32 hashy(const char* str)
{
	uint32 h = 0;
	char* p = nullptr;

	for (p = (char*)str; *p != '\0'; p++)
		h = 37 * h + *p;
	return h; // or, h % ARRAY_SIZE;
}

enum CompType
{
	VEHICLE = hashy("VEHICLE"),
	RIGIDBODY = hashy("RIGIDBODY"),
	POLYRENDERER = hashy("POLYRENDERER"),
};

struct Component
{
	CompType type;
	void (*Init_References)(Component* component, GameObject* gameObject);
	void (*Delete)(Component* component, GameState* gameState);

	uint16 id;
	uint16 gameObjectId;
	GameObject* gameObject;
};