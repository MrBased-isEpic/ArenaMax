#pragma once

#include "render.h"
#include "component2.h"

Component* Polyrenderer_Create(
	ComponentForm* form,
	GameState* gameState,
	GameObject* gameObject);

struct PolyrendererForm
{
	ComponentForm form =
	{
		POLYRENDERER,
		sizeof(PolyrendererForm),
		&Polyrenderer_Create
	};

	uint8 noOfSides = 0;
	real32 radius = 0;
	Color color = ORANGE;
	real32 rotationOffset = 0;
};
