#include "collider.h"

void Collider_CalculateNormals(Collider collider)
{
	if (collider.points == nullptr)
	{
		cout << "Collider points pointer not initialized" << endl;
		return;
	}
	if (collider.normals = nullptr)
	{
		cout << "Collider normals pointer not initialized" << endl;
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