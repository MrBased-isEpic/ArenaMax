#pragma once

#include "raylib.h"
#include "physics.h"
#include "render.h"

struct Component
{

};


struct GameObject
{
	Transform transform;
	RigidBody* rigidbody;
	uint16 rigidbodyid;

	ShapeRenderer* shape;
	uint16 renderId;
};

GameObject GameObjectCreate();