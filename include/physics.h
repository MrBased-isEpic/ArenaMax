#pragma once

struct PhysicsState;

#include "types.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "arrays.h"
#include <iostream>
#include "debug.h"
#include "rigidbody.h"
#include <cfloat>

using namespace std;

#define CIRCLE 0
#define SQUARE 1
#define RECTANGLE 2


// A report of a intersection happening between rigidbodies.
// Contains everything that is needed to resolve the collision.
struct Collision
{
	RigidBody* self;
	RigidBody* other;

	Vector3 mtv;
};

struct PhysicsState
{
	uint16 rigidbodyIdCount = 0;

	// List of rigidbodies that can move across the world
	SwapBackArray dynamics;
	//vector<RigidBody> dynamics = vector<RigidBody>(0);
	bool isDynamicsRearranged = false;

	// List of collisions that occurred this frame. 
	// The game or the physics engine fetches it from here
	// so it can resolve them.
	vector<Collision> collisions = vector<Collision>(0);
};

bool Physics_GetCollision(
	PhysicsState* physicsState,
	RigidBody* rb,
	Collision* col);

PhysicsState* Physics_Start();

void Physics_Update(
	PhysicsState* physicsState,
	real32 timeStep);


RigidBody* Physics_GetRigidBody(
	PhysicsState* physicsState,
	uint16 id);

uint16 Physics_AddRigidBody(
	PhysicsState* physicsState,
	Transform* transform,
	RigidBody** rigidBody,
	Vector3 points[],
	uint8 numberOfPoints,
	bool isStatic);

//Component* Physics_AddRigidBody(
//	GameState* gameState,
//	GameObject* gameObject,
//	ComponentForm* form);

void Physics_DeleteRigidBody(
	PhysicsState* physicsState,
	RigidBody** rigidBody,
	uint16 rigidbodyid);
