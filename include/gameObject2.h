#pragma once

#include "gameObject.h"
#include "gameState.h"
#include "component2.h"

struct GameObjectForm
{
	char name[64];
	uint16 noOfComponents = 0;
};


GameObject* GameObject_Create(GameState* gameState, GameObjectForm* form = nullptr);

void GameObject_Delete(
	GameState* gameState,
	uint16 gameObjectId);

void GameObject_AddComponent(
	GameObject* gameObject,
	GameState* gameState,
	ComponentForm* form);

Component* GameObject_GetComponent(
	GameObject* gameObject,
	CompType type);

GameObjectForm* GameObject_GetForm(GameObject* gameObject);