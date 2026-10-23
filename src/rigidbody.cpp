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
	rb.component.gameObjectId = gameObject->id;

	SwapBackArray_Add(&physicsState->dynamics, (void*)&rb);

	RigidBody* rbPtr = (RigidBody*)SwapBackArray_Last(&physicsState->dynamics);

	return (Component*)rbPtr;
}

void RigidBody_Update(
	RigidBody* rigidbody,
	real32 timeStep)
{
	if (rigidbody->isStatic) return;

	Transform* t = rigidbody->transform;

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