#pragma once

struct GameObject;
struct GameState;
struct ComponentForm;

#include "raylib.h"
#include "types.h"
#include "arrays.h"

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

	//TODO : Define Create Function here as well.

	//Take References to whatever component it wants.
	//Can be used for refreshing references.
	//TODO : Make Default funtion which refreshes gameObject reference.
	void (*Init_References)(Component* component, GameObject* gameObject);
	void (*Delete)(Component* component, GameState* gameState);

	ComponentForm* (*GetForm)(Component* component);

	uint16 id;
	uint16 gameObjectId;
	GameObject* gameObject;
};

Component* Component_GetWithId(
	SwapBackArray* array,
	uint16 gameObjectId,
	uint16* index);