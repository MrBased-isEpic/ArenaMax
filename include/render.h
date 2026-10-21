#pragma once

struct Component;

#include "component.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"
#include <vector>

using namespace std;

struct PolyRenderer
{
	Component component;

	Transform* transform = nullptr;
	uint8 noOfSides = 4;
	real32 size = 15;
	Color color = ORANGE;
	real32 rotationOffset = 45;
};

struct RenderState
{
	uint16 rendererIdCount = 0;

	// List of shapes to be rendered
	vector<PolyRenderer> shapes = vector<PolyRenderer>(0);
	bool isShapesRearranged = false;
};

RenderState* Renderer_Start();

uint16 ShapeRenderer_Create(
	RenderState* renderState,
	Transform* transform,
	PolyRenderer** shapeRenderer,
	uint8 numberOfSides,
	real32 size,
	Color color);

void Renderer_Update(RenderState* renderState);