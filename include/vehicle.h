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

void Vehicle_InitReferences(
    Component* component,
    GameObject* gameObject);

ComponentForm* Vehicle_GetForm(Component* component);

struct Vehicle
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

void Vehicle_Update(
    Vehicle* vehicle,
    Input input,
    real32 timeStep);