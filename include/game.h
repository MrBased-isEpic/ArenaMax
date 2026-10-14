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
#include <vector>

struct GameState
{
    uint16 screenWidth;
    uint16 screenHeight;

    PhysicsState* physicsState;
    RenderState* renderState;

    //uint16 gameObjectIdCount = 0;
    //vector<GameObject> gameObjects = vector<GameObject>(0);
    //bool isGameObjectRearranged = false;

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