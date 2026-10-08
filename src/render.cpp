#include "render.h"

RenderState* Renderer_Start()
{
	RenderState* renderState = new RenderState;
	renderState->shapes.reserve(5);
	return renderState;
}

void Renderer_Update(RenderState* renderState)
{
	for (int i = 0; i < renderState->shapes.size(); i++)
	{
		ShapeRenderer sr = renderState->shapes[i];
		Transform transform = *sr.transform;

		DrawPoly(
			transform.translation.xy,
			sr.noOfSides,
			sr.size,
			(QuaternionToEuler(transform.rotation).z *
				RAD2DEG) + sr.rotationOffset,
			sr.color);
	}
}

uint16 ShapeRenderer_Create(
	RenderState* renderState,
	Transform* transform,
	ShapeRenderer** shapeRenderer,
	uint8 numberOfSides,
	real32 size,
	Color color)
{
	ShapeRenderer sr = {};
	sr.noOfSides = numberOfSides;
	sr.size = size;
	sr.color = color;
	sr.rotationOffset = 0;

	sr.transform = transform;

	sr.id = renderState->rendererIdCount++;

	renderState->shapes.push_back(sr);

	*shapeRenderer = &renderState->shapes.back();

	return sr.id;
}