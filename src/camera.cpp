#include "camera.h"


Camera2D Camera_Create(GameState* gameState)
{
    Camera2D camera = { 0 };

    camera.target = gameState->vehicle.gameObject.transform.translation.xy;

    camera.offset = {
        gameState->screenWidth / 2.0f,
        gameState->screenHeight / 2.0f };

    camera.zoom = 1;

    return camera;
}

void Camera_Update(GameState* gameState)
{
    gameState->camera.target = gameState->vehicle.gameObject.transform.translation.xy;
}