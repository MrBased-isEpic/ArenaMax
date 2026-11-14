#pragma once

#include "vehicle.h"
#include "component2.h"
#include "gameObject2.h"
#include "rigidbodyform.h"

Component* Vehicle_Create(
	ComponentForm* form,
	GameState* gameState,
	GameObject* gameObject);


struct VehicleForm
{
	ComponentForm form =
	{
		VEHICLE,
		sizeof(VehicleForm),
		&Vehicle_Create
	};

	real32 maxSpeed = 600;
	real32 acceleration = 500;
	real32 deceleration = 100;

	real32 rotationAcceleration = 891;
	real32 maxRotationSpeed = 270;

	real32 maxSideWaysFriction = 500;
};