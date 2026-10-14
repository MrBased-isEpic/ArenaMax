#pragma once

struct GameObject;
struct GameState;

#include "types.h"

enum CompType
{
	NONE,
	LOGIC,
	RIGIDBODY,
	POLYRENDERER
};

struct Component
{
	CompType type;
	uint16 id;
	uint16 gameObjectId;
};

struct ComponentForm
{
	CompType type;
	uint16 size;

	Component* (*Create)(GameState* gameState, GameObject* gameObject, ComponentForm* form);
};

//struct LogicComponent
//{
//	Component component =
//	{
//		LOGIC,
//		0
//	};
//
//	void (*SelfInitialize)();
//	void (*RefInitialize)(GameObject* gameObject);
//};
