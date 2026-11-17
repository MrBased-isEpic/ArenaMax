#include "collider.h"

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