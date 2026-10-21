#include "component.h"
#include "rigidbody.h"
#include "component2.h"


Component* RigidBody_Create(
	GameState* gameState,
	GameObject* gameObject,
	ComponentForm* form)
{
	///cout << endl << "Creating a Rigidbody.." << endl;

	RigidBody rb = {};
	RigidbodyForm* rbForm = (RigidbodyForm*)form;
	PhysicsState* physicsState = gameState->physicsState;


	rb.component.type = RIGIDBODY;
	rb.velocity = { 0,0,0 };
	rb.angularVelocity = { 0,0,0 };
	rb.transform = &gameObject->transform;
	rb.numberOfPoints = rbForm->numberOfPoints;

	Matrix mat = MatrixCompose(
		rb.transform->translation,
		rb.transform->rotation,
		rb.transform->scale);

	if (rbForm->numberOfPoints == 1)
	{
		rbForm->numberOfPoints = 2;
	}

	for (int i = 0; i < rbForm->numberOfPoints; i++)
	{
		rb.points[i] = Vector3Transform(rbForm->points[i], mat);
		//cout <<rb.points[i].x << ":" << rb.points[i].y << endl;
	}

	Rigidbody_GetNormals(&rb);

	rb.isStatic = rbForm->isStatic;
	rb.component.id = physicsState->rigidbodyIdCount++;

	SwapBackArray_Add(&physicsState->dynamics, (void*)&rb);

	RigidBody* rbPtr = (RigidBody*)SwapBackArray_Last(&physicsState->dynamics);

	return (Component*)rbPtr;
}