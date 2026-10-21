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