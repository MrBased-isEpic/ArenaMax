#pragma once
struct GameState;

#include "types.h"
#include "input.h"
#include "vehicle.h"
#include "raylib.h"
#include "physics.h"
#include "gameObject.h"
#include "render.h"
#include "camera.h"

struct GameState
{
    uint16 screenWidth;
    uint16 screenHeight;

    PhysicsState* physicsState;
    RenderState* renderState;

    Vehicle vehicle;

    GameObject box;
    Input input;

    Camera2D camera;
};


GameState* Logic_Start(
    uint16 screenWidth,
    uint16 screenHeight,
    PhysicsState* physicsState,
    RenderState* renderState);

void GetInput(GameState* gameState);

void Logic_Update(GameState* gameState, real32 timeStep);