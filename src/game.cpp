#include "gameState.h"
#include "logic.h"

GameState* Logic_Start(
    uint16 screenWidth,
    uint16 screenHeight,
    PhysicsState* physicsState,
    RenderState* renderState)
{
    GameState* gameState = (struct GameState*)malloc(sizeof(struct GameState));

    gameState->screenWidth = screenWidth;
    gameState->screenHeight = screenHeight;

    gameState->physicsState = physicsState;
    gameState->renderState = renderState;

    gameState->input = {};

    Vehicle_Create(&gameState->vehicle, gameState->physicsState);

    gameState->box = {};
    GameObject* box = &gameState->box;

    box->transform.translation = {500,100,0};
    box->transform.rotation = QuaternionFromEuler(0, 0, -90 * DEG2RAD);
    box->transform.scale = { 1,1,1 };

    box->renderId = ShapeRenderer_Create(
        gameState->renderState, 
        &box->transform,
        &box->shape,
        5,
        300,
        GRAY);

    Vector3 points[5];
    GeneratePolyPoints(points, 5, 300);
    
    box->rigidbodyid = Physics_AddRigidBody(
        physicsState,
        &box->transform,
        &box->rigidbody,
        points,
        5,
        false);

    gameState->camera = Camera_Create(gameState);

    return gameState;
}

void Logic_RefreshPhysicsReferences(GameState* gameState)
{
    if (!gameState->physicsState->isDynamicsRearranged) return;

    gameState->vehicle.gameObject.rigidbody = Physics_GetRigidBody(
        gameState->physicsState,
        gameState->vehicle.gameObject.rigidbodyid);

    gameState->box.rigidbody = Physics_GetRigidBody(
        gameState->physicsState,
        gameState->box.rigidbodyid);

    gameState->physicsState->isDynamicsRearranged = false;

    cout << "refreshed references" << endl;
}

void Logic_RefreshGameObjectReferences(GameState* gameState)
{
    //if (!gameState->isGameObjectRearranged) return;

    
}

void GetInput(GameState* gameState)
{
    Input_Get(&gameState->input);
}

void Logic_Update(GameState* gameState, real32 timeStep)
{
    Logic_RefreshPhysicsReferences(gameState);

    Vehicle_Update(
        &gameState->vehicle,
        gameState->input,
        timeStep);

    Camera_Update(gameState);
}