#pragma once
struct GameState;
struct Component;

#include "types.h"
#include "arrays.h"
#include "input.h"
#include "vehicle.h"
#include "raylib.h"
#include "physics.h"
#include "gameObject.h"
#include "render.h"
#include "camera.h"
#include <vector>

struct GameState
{
    uint16 screenWidth;
    uint16 screenHeight;

    PhysicsState* physicsState;
    RenderState* renderState;

    uint16 gameObjectIdCount = 0;
    SwapBackArray gameObjects;
    bool isGameObjectRearranged = false;

    Vehicle vehicle;
    Input input;

    Camera2D camera;
};


