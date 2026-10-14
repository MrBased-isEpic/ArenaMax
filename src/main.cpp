#include <iostream>
#include "types.h"
#include "vehicle.h"
#include "render.h"
#include "game.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "debug.h"

using namespace std;


void GenerateTrianglePlots(
    Vector2* v1,
    Vector2* v2,
    Vector2* v3,
    float size,
    Transform transform)
{
    Matrix mat = MatrixCompose(
        transform.translation,
        transform.rotation,
        transform.scale);

    v1->x = size;
    v1->y = size;

    v2->x = 0;
    v2->y = -size;

    v3->x = -size;
    v3->y = size;

    *v1 = Vector2Transform(*v1, mat);
    *v2 = Vector2Transform(*v2, mat);
    *v3 = Vector2Transform(*v3, mat);
}



int main()
{
	uint16 screenWidth = 1280;
    uint16 screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    real32 targetFPS = 60;
	SetTargetFPS(targetFPS);

    real32 targetFrameTime = 1 / targetFPS;

    PhysicsState* physicsState = Physics_Start();
    RenderState* renderState = Renderer_Start();
    GameState* gameState = Logic_Start(
        screenWidth,
        screenHeight,
        physicsState,
        renderState);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        GetInput(gameState);

        Logic_Update(gameState, targetFrameTime);
        Physics_Update(physicsState, targetFrameTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(gameState->camera);

        //Draw Grid
        rlPushMatrix();
        rlTranslatef(0, 25*40, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, 30);
        rlPopMatrix();

        Renderer_Update(renderState);
        
        GameObject* gameObject = &gameState->vehicle.gameObject;

        Vector2 v1, v2, v3;
        GenerateTrianglePlots(
            &v1,
            &v2,
            &v3,
            15,
            gameObject->transform);

        DrawTriangle(v1, v2, v3, BLUE);

        DrawColliders(physicsState);

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    free(gameState);
    free(physicsState);


    return 0;
}