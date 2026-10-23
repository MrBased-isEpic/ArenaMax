#pragma once

#include "gameObject.h"
#include "gameState.h"
#include "component2.h"

GameObject* GameObject_Create(GameState* gameState);

void GameObject_Delete(
	GameState* gameState,
	uint16 gameObjectId);

void GameObject_AddComponent(
	GameObject* gameObject,
	GameState* gameState,
	ComponentForm* form);