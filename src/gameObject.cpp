#include "gameObject.h"
#include "gameObject2.h"

GameObject* GameObject_Create(GameState* gameState)
{
	GameObject gameObject = {};
	gameObject.id = gameState->gameObjectIdCount++;

	SwapBackArray_Add(&gameState->gameObjects, &gameObject);
	
	return (GameObject*)SwapBackArray_Last(&gameState->gameObjects);
}

void GameObject_Delete(
	GameState* gameState,
	uint16 gameObjectId)
{
	GameObject gm = {};

	//for (int i = 0; i < gameState->gameObjects.size(); i++)
	//{
	//	if (gameState->gameObjects[i].id == gameObjectId)
	//	{
	//		gm = gameState->gameObjects[i];
	//		gameState->gameObjects[i] = gameState->gameObjects.back();
	//		gameState->gameObjects.pop_back();
	//		break;
	//	}
	//}
	//
	//gameState->isGameObjectRearranged = true;
	// loop thru components to take care of deletions
}

void GameObject_AddComponent(
	GameObject* gameObject,
	GameState* gameState,
	ComponentForm* form)
{
	if (gameObject->componentsCount == 5) return;

	Component* component =
		form->Create(form, gameState, gameObject);

	component->Init_References(component, gameObject);

	gameObject->components[gameObject->componentsCount++] = component;
}

Component* GameObject_GetComponent(
	GameObject* gameObject,
	uint32 type)
{
	for (int i = 0; i < gameObject->componentsCount; i++)
	{
		if (gameObject->components[i]->type == type)
			return gameObject->components[i];
	}

	cout << "could not find requested component" << endl;
	return nullptr;
}