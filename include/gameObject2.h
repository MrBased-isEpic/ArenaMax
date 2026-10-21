#pragma once

#include "gameObject.h"
#include "gameState.h"
#include "component2.h"

//GameObject GameObjectCreate(GameState* gameState);

void GameObject_Delete(
	GameState* gameState,
	uint16 gameObjectId);

void GameObject_AddComponent(
	GameObject* gameObject,
	GameState* gameState,
	ComponentForm* form);