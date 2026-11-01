#include "rigidbody.h"
#include "rigidbodyform.h"

Component* RigidBody_Create(ComponentForm* form, GameState* gameState, GameObject* gameObject)
{
	///cout << endl << "Creating a Rigidbody.." << endl;

	RigidBody rb = {};
	RigidbodyForm* rbForm = (RigidbodyForm*)form;
	PhysicsState* physicsState = gameState->physicsState;

	rb.component.type = RIGIDBODY;
	rb.component.id = physicsState->rigidbodyIdCount++;
	rb.component.gameObjectId = gameObject->id;
	rb.component.gameObject = gameObject;

	rb.velocity = { 0,0,0 };
	rb.angularVelocity = { 0,0,0 };
	rb.numberOfPoints = rbForm->numberOfPoints;

	Transform* t = &gameObject->transform;

	Matrix mat = MatrixCompose(
		t->translation,
		t->rotation,
		t->scale);

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

	SwapBackArray_Add(&physicsState->dynamics, (void*)&rb);

	RigidBody* rbPtr = (RigidBody*)SwapBackArray_Last(&physicsState->dynamics);

	return (Component*)rbPtr;
}

void RigidBody_InitReferences(Component* component, GameObject* gameObject)
{
	return;
}


void RigidBody_Update(
	RigidBody* rigidbody,
	real32 timeStep)
{
	if (rigidbody->isStatic) return;

	Transform* t = &rigidbody->component.gameObject->transform;

	// Apply Velocity to given transform

	Vector3 positionChange = Vector3Scale(rigidbody->velocity, timeStep);

	t->translation = Vector3Add(
		t->translation,
		positionChange);

	Vector3 angularVelocity = Vector3Scale(
		rigidbody->angularVelocity,
		timeStep);

	Quaternion rotChange = QuaternionFromEuler(
		angularVelocity.x,
		angularVelocity.y,
		angularVelocity.z);

	t->rotation = QuaternionMultiply(
		t->rotation,
		rotChange);

	for (int i = 0; i < rigidbody->numberOfPoints; i++)
	{
		rigidbody->points[i] = Vector3Add(
			rigidbody->points[i],
			positionChange);

		Vector3 localPoint = rigidbody->points[i] - t->translation;

		rigidbody->points[i] = Vector3RotateByQuaternion(
			localPoint,
			rotChange) + t->translation;
	}
}