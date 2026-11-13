#include "vehicle.h"
#include "vehicleform.h"

using namespace std;

Component* Vehicle_Create(ComponentForm* form, GameState* gameState, GameObject* gameObject)
{
    Vehicle vehicle = {};

    VehicleForm* vehicleForm = (VehicleForm*)form;

    Transform* transform = &gameObject->transform;
    transform->translation = { 0, 0 };
    transform->rotation = { 0,0,0,1 };
    transform->scale = { 1,1,1 };

    vehicle.maxSpeed = vehicleForm->maxSpeed;
    vehicle.acceleration = vehicleForm->acceleration;
    vehicle.deceleration = vehicleForm->deceleration;

    vehicle.maxRotationSpeed = vehicleForm->maxRotationSpeed;
    vehicle.rotationAcceleration = vehicleForm->rotationAcceleration;
    vehicle.maxSideWaysFriction = vehicleForm->maxSideWaysFriction;

    RigidbodyForm rbForm = {};
    
    rbForm.numberOfPoints = 4;
    rbForm.isStatic = false;
    
    GeneratePolyPoints(rbForm.points, rbForm.numberOfPoints, 21.2);
    GameObject_AddComponent(gameObject, gameState, (ComponentForm*) &rbForm);

    gameState->vehicle = vehicle;
    gameState->vehicle.component.gameObject = gameObject;

    return (Component*)&gameState->vehicle;
}

void Vehicle_InitReferences(Component* component, GameObject* gameObject)
{
    return;
}


void Vehicle_Update(
    Vehicle* vehicle,
    Input input,
    float timeStep)
{
    GameObject* gameObject = vehicle->component.gameObject;
    RigidBody* rb = (RigidBody*)GameObject_GetComponent(gameObject, RIGIDBODY);

    Vector3* velocity = &(rb->velocity);

    real32* angularVelocity = &(rb->angularVelocity.z);

    *angularVelocity *= RAD2DEG;

    Vector3 forward = TransformGetForward(gameObject->transform);
    Vector3 velocityDir = Vector3Normalize(*velocity);

    // Acceleration / Deceleration
    if (input.forward)
    {
        Vector3 forward = { 0,-1,0 };
        forward = Vector3Transform(
            forward,
            QuaternionToMatrix(gameObject->transform.rotation));

        Vector3 deceleration = Vector3Scale(
            forward,
            vehicle->acceleration * timeStep);

        *velocity = Vector3Add(
            *velocity,
            deceleration);

        *velocity = Vector3ClampValue(
            *velocity,
            0,
            vehicle->maxSpeed);
    }
    else if (Vector3Length(*velocity) > 0.01f)
    {
        Vector3 directionToDecelerate = Vector3Negate(velocityDir);

        Vector3 velocityChange = Vector3Scale(
            directionToDecelerate,
            vehicle->deceleration * timeStep);

        *velocity = Vector3Add(
            *velocity,
            velocityChange);

        if (Vector3Length(*velocity) < 0.01f)
            *velocity = {};
    }

    // Rotation
    real32 rotationDir = 0;
    rotationDir += -input.left;
    rotationDir += input.right;

    Vector3 rotAxis = { 0,0,1 };

    if (rotationDir != 0) //User is pressing steering inputs
    {
        *angularVelocity +=
            (vehicle->rotationAcceleration * rotationDir) * timeStep;

        *angularVelocity = Clamp(
            *angularVelocity,
            -vehicle->maxRotationSpeed,
            vehicle->maxRotationSpeed);
    }
    else if (Abs(*angularVelocity) > 0)
    {
        real32 dir = *angularVelocity > 0 ? -1 : 1;

        *angularVelocity +=
            (vehicle->rotationAcceleration * dir) * timeStep;

        if (Abs(*angularVelocity) < 5)
        {
            *angularVelocity = 0;
        }
    }

    *angularVelocity *= DEG2RAD;

    // Subtly rotate velocity towards vehicle forward.

    Vector2 velocityDir2D = velocityDir.xy;
    Vector2 forward2D = forward.xy;

    real32 angle = -Vector2Angle(
        forward2D,
        velocityDir2D);

    *velocity = Vector3RotateByAxisAngle(
        *velocity,
        { 0,0,1 },
        angle * timeStep);


    // If vehicle not aligned with current velocity, lower velocity
    // Friction simulation
    real32 rotationBasedDeceleration = Vector3DotProduct(
        forward,
        Vector3Normalize(*velocity));

    rotationBasedDeceleration = Clamp(
        Abs(rotationBasedDeceleration),
        0,
        1);

    rotationBasedDeceleration = 1 - rotationBasedDeceleration;

    Vector3 directionToDecelerate = Vector3Negate(velocityDir);

    Vector3 deceleration = Vector3Scale(
        directionToDecelerate,
        (vehicle->maxSideWaysFriction * rotationBasedDeceleration) *
        timeStep);

    *velocity = Vector3Add(
        *velocity,
        deceleration);

    if (Vector3Length(*velocity) < 0.01f)
        *velocity = {};
}

ComponentForm* Vehicle_GetForm(Component* component)
{
    Vehicle* vehicle = (Vehicle*)component;
    VehicleForm* vForm = (VehicleForm*)malloc(sizeof(VehicleForm));

    *vForm = {};
    vForm->maxSpeed = vehicle->maxSpeed;
    vForm->acceleration = vehicle->acceleration;
    vForm->deceleration = vehicle->deceleration;

    vForm->rotationAcceleration = vehicle->rotationAcceleration;
    vForm->maxRotationSpeed = vehicle->maxRotationSpeed;

    vForm->maxSideWaysFriction = vehicle->maxSideWaysFriction;

    return (ComponentForm*)vForm;
}