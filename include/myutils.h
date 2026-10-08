#pragma once
#include "raylib.h"
#include "raymath.h"
#include "types.h"
#include <cmath>

real32 Abs(float x);

Vector3 TransformGetForward(Transform transform);

void GenerateSquarePoints(Vector3* points, real32 size);

void GeneratePolyPoints(
	Vector3 points[],
	uint8 numberOfPoints,
	real32 size);