#pragma once
#include "types.h"
#include "physics.h"
#include "raylib.h"
#include "input.h"
#include "gameObject.h"
#include "myutils.h"

using namespace std;

struct Vehicle
{
    GameObject gameObject;

    //Vector3 velocity;
    real32 acceleration;
    real32 deceleration;
    real32 maxSpeed;

    real32 rotationAcceleration;
    real32 maxRotationSpeed;

    real32 maxSideWaysFriction;
};

void Vehicle_Create(
    Vehicle* vehicle,
    PhysicsState* physicsState);

void Vehicle_Update(
    Vehicle* vehicle,
    Input input,
    real32 timeStep);