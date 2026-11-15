#include "gameObject.h"
#include "gameObject2.h"


GameObject* GameObject_Create(GameState* gameState, GameObjectForm* form)
{
	GameObject gameObject = {};
	gameObject.id = gameState->gameObjectIdCount++;

	SwapBackArray_Add(&gameState->gameObjects, &gameObject);

	if (form == nullptr)
	{
		return (GameObject*)SwapBackArray_Last(&gameState->gameObjects);
	}

	GameObject* gameObjectRef = (GameObject*)SwapBackArray_Last(&gameState->gameObjects);
	
	memcpy(gameObjectRef->name, form->name, sizeof(gameObjectRef->name));
	
	ComponentForm* componentIterator = (ComponentForm*)(form + 1);
	for (int i = 0; i < form->noOfComponents; i++)
	{
		GameObject_AddComponent(gameObjectRef, gameState, componentIterator);
		componentIterator = (ComponentForm*)((uint8)componentIterator + componentIterator->size);
	}

	return gameObjectRef;
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
	CompType type)
{
	for (int i = 0; i < gameObject->componentsCount; i++)
	{
		if (gameObject->components[i]->type == type)
			return gameObject->components[i];
	}

	cout << "could not find requested component" << endl;
	return nullptr;
}

void GameObject_SetComponentReference(
	GameObject* gameObject,
	Component* newAddress)
{
	for (int i = 0; i < gameObject->componentsCount; i++)
	{
		if (gameObject->components[i]->type == newAddress->type)
		{
			gameObject->components[i] = newAddress;
			return;
		}
	}

	cout << "Could Not Find Specified Component Type in GameObject." << endl;
}

void GameObject_RemoveComponentReference(
	GameObject* gameObject,
	Component* component)
{
	for (int i = 0; i < gameObject->componentsCount; i++)
	{
		if (gameObject->components[i]->type == component->type)
		{
			gameObject->components[i] = nullptr;
			return;
		}
	}

	cout << "Could Not Find Specified Component Type in GameObject." << endl;
}

GameObjectForm* GameObject_GetForm(GameObject* gameObject)
{
	Component** references = &gameObject->components[0];
	Component** lastReference = references + (gameObject->componentsCount - 1);

	LinearAllocator gameObjectFormStore = LinearAllocator_Create(1024);

	GameObjectForm* gForm = (GameObjectForm*)LinearAllocator_Push(
		&gameObjectFormStore,
		sizeof(GameObjectForm));

	memcpy(gForm->name, gameObject->name, sizeof(gForm->name));
	gForm->noOfComponents = gameObject->componentsCount;

	Component** iterator = references;
	while (iterator <= lastReference)
	{
		ComponentForm* form = (*iterator)->GetForm(*iterator);
		void* copyDst = LinearAllocator_Push(&gameObjectFormStore, form->size);
		memcpy(copyDst, form, form->size);
		free(form);
		iterator++;
	}

	uint16 gFormSize = LinearAllocator_Size(&gameObjectFormStore);

	GameObjectForm* result = (GameObjectForm*)malloc(gFormSize);
	memcpy(result, gForm, gFormSize);

	LinearAllocator_Delete(&gameObjectFormStore);

	return gForm;
}