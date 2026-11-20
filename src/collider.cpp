#include "collider.h"
#include "physics.h"

Collider Collider_Create(PhysicsState* physicsSatte, uint8 noOfSides)
{
	Collider collider = {};
	collider = {};
	collider.noOfSides = 5;

	collider.points = (Vector3*)LinearAllocator_Push(&physicsSatte->points,
		sizeof(Vector3) * collider.noOfSides);
	collider.normals = (Vector3*)LinearAllocator_Push(&physicsSatte->normals,
		sizeof(Vector3) * collider.noOfSides);

	return collider;
}

void Collider_CalculateNormals(Collider collider)
{
	if (collider.points == nullptr)
	{
		LogError("Collider points pointer not initialized")
		return;
	}
	if (collider.normals = nullptr)
	{
		LogError("Collider normals pointer not initialized")
		return;
	}

	SwapBackArray points = SwapBackArray_Create(
		sizeof(Vector3),
		collider.noOfSides,
		collider.points,
		collider.noOfSides);

	SwapBackArray normals = SwapBackArray_Create(
		sizeof(Vector3),
		collider.noOfSides,
		collider.normals);

	for (int i = 0; i < collider.noOfSides; i++)
	{
		Vector3 edge = Vector3Subtract(
			*(Vector3*)SwapBackArray_Get(&points, (i + 1) % collider.noOfSides),
			*(Vector3*)SwapBackArray_Get(&points, i));

		Vector3 normal = Vector3Normalize(perp(edge));
		SwapBackArray_Add(&points, &normal);
	}
}