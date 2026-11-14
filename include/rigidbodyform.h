#pragma once

#include "rigidbody.h"
#include "component2.h"

Component* RigidBody_Create(
	ComponentForm* form,
	GameState* gameState,
	GameObject* gameObject);

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