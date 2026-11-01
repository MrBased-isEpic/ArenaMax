#pragma once

#include "component.h"
#include "gameState.h"
#include "gameObject.h"


struct ComponentForm
{
	CompType type;
	uint16 size;

	Component* (*Create)(ComponentForm* form, GameState* gameState, GameObject* gameObject);
};


struct GameObjectForm
{
	uint16 size;
	ComponentForm firstComponent;
};
