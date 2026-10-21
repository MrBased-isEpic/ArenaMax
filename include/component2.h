#pragma once

#include "component.h"
#include "gameState.h"
#include "gameObject.h"


struct ComponentForm
{
	CompType type;
	uint16 size;

	Component* (*Create)(GameState* gameState, GameObject* gameObject, ComponentForm* form);
};

struct LogicComponent
{
	Component component =
	{
		LOGIC,
		0
	};

	void (*SelfInitialize)();
	void (*RefInitialize)(GameObject* gameObject);
};


struct GameObjectForm
{
	uint16 size;
	ComponentForm firstComponent;
};

struct RigidbodyForm 
{
	Vector3 points[5];
	uint8 numberOfPoints;
	bool isStatic;
};


Component* RigidBody_Create(
	GameState* gameState,
	GameObject* gameObject,
	ComponentForm* form);