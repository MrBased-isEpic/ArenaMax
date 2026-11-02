#pragma once

#include "component.h"
#include "gameState.h"
#include "gameObject.h"


struct ComponentForm
{
	uint32 type;
	uint16 size;

	Component* (*Create)(ComponentForm* form, GameState* gameState, GameObject* gameObject);
};


struct GameObjectForm
{
	uint16 size;
	ComponentForm firstComponent;
};
