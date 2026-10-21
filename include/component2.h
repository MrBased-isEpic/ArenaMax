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

Component* RigidBody_Create(
	GameState* gameState,
	GameObject* gameObject,
	ComponentForm* form);

struct RigidbodyForm 
{
	ComponentForm form = 
	{
		RIGIDBODY,
		sizeof(RigidbodyForm),
		&RigidBody_Create
	};

	Vector3 points[5];
	uint8 numberOfPoints = 0;
	bool isStatic = true;
};