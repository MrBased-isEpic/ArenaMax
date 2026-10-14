#pragma once

#include "component.h"
#include "raylib.h"
#include "raymath.h"

struct RigidBodyForm
{
	//ComponentForm form = {
	//	RIGIDBODY,
	//	sizeof(RigidBodyForm),
	//	&Physics_AddRigidBody
	//};

	Vector3 points[5];
	uint8 numberOfPoints;
	bool isStatic;
};

struct RigidBody
{
	Component component =
	{
		RIGIDBODY,
	};

	bool isStatic = true;
	Transform* transform = nullptr;

	// world space position of the collider points.
	Vector3 points[5];

	// The outwards direction each edge points towards.
	// Calculated per frame for dynamic objects, once if static.
	Vector3 normals[5];

	// Number of points define the shape of the collider.
	uint8 numberOfPoints = 0;

	// units in pixels per second
	Vector3 velocity = {};
	// units in radians per second
	Vector3 angularVelocity = {};

	real32 bounce = .2f;
};

void RigidBody_Update(
	RigidBody* rigidbody,
	real32 timeStep);

//Component* Physics_AddRigidBody(
//	GameState* gameState,
//	GameObject* gameObject,
//	ComponentForm* form);