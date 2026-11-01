#pragma once
#include "types.h"
#include "rigidbody.h"
#include "physics.h"
#include "raylib.h"
#include "component.h"
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

void Vehicle_InitReferences(
    Component* component,
    GameObject* gameObject);

struct Vehicle2
{
    Component component =
    {
        VEHICLE,
        &Vehicle_InitReferences
    };

    real32 acceleration;
    real32 deceleration;
    real32 maxSpeed;

    real32 rotationAcceleration;
    real32 maxRotationSpeed;

    real32 maxSideWaysFriction;
};

void Vehicle2_Update(
    Vehicle2* vehicle,
    Input input,
    real32 timeStep);

//void Vehicle_Create(
//    Vehicle* vehicle,
//    PhysicsState* physicsState);

void Vehicle_Update(
    Vehicle* vehicle,
    Input input,
    real32 timeStep);