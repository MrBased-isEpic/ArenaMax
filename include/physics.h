#pragma once

struct PhysicsState;
#include "types.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>
#include "debug.h"
#include <cfloat>

using namespace std;

#define CIRCLE 0
#define SQUARE 1
#define RECTANGLE 2

struct RigidBody
{
	uint16 id;

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
	vector<RigidBody> dynamics = vector<RigidBody>(0);
	bool isDynamicsRearranged = false;

	// List of collisions that occurred this frame. 
	// The game or the physics engine fetches it from here
	// so it can resolve them.
	vector<Collision> collisions = vector<Collision>(0);
};

bool RigidBody_GetCollision(
	PhysicsState* physicsState,
	RigidBody* rb,
	Collision* col);

PhysicsState* Physics_Start();

void Physics_Update(
	PhysicsState* physicsState,
	real32 timeStep);

void RigidBody_Update(
	RigidBody* rigidbody,
	real32 timeStep);

RigidBody* RigidBody_Get(
	PhysicsState* physicsState,
	uint16 id);

uint16 Rigidbody_Create(
	PhysicsState* physicsState,
	Transform* transform,
	RigidBody** rigidBody,
	Vector3 points[],
	uint8 numberOfPoints,
	bool isStatic);

void Rigidbody_Delete(
	PhysicsState* physicsState,
	RigidBody** rigidBody,
	uint16 rigidbodyid);
