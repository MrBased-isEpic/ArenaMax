#include "rigidbody.h"

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