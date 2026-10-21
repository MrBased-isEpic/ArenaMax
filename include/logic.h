#pragma once

#include "gameState.h"

GameState* Logic_Start(
    uint16 screenWidth,
    uint16 screenHeight,
    PhysicsState* physicsState,
    RenderState* renderState);

void GetInput(GameState* gameState);

void Logic_Update(GameState* gameState, real32 timeStep);