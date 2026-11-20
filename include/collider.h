#pragma once

#include "types.h"
#include "debug.h"
#include "myutils.h"
#include "arrays.h"
#include "raylib.h"
#include "raymath.h"

struct PhysicsState;

struct Collider
{
	uint8 noOfSides = 0;
	Vector3* points = nullptr;
	Vector3* normals = nullptr;
};

Collider Collider_Create(PhysicsState* physicsSatte, uint8 noOfSides);

void Collider_CalculateNormals(Collider collider);
