#pragma once

#include "vehicle.h"
#include "raylib.h"
#include "gameState.h"
#include "raylib.h"

Camera2D Camera_Create(GameState* gameState);

void Camera_Update(GameState* gameState);