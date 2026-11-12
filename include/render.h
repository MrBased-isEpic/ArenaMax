#pragma once

struct Component;

#include "component.h"
#include "raylib.h"
#include "raymath.h"
#include "types.h"
#include "arrays.h"
#include <vector>

using namespace std;

void PolyRenderer_InitReferences(
	Component* component,
	GameObject* gameObject);

void PolyRenderer_Delete(
	Component* component,
	GameState* gameState);

struct PolyRenderer
{
	Component component = 
	{
		POLYRENDERER,
		&PolyRenderer_InitReferences,
		&PolyRenderer_Delete
	};

	Transform* transform = nullptr;
	uint8 noOfSides = 4;
	real32 size = 15;
	Color color = ORANGE;
	real32 rotationOffset = 45;
};

struct RenderState
{
	// List of shapes to be rendered
	SwapBackArray polys;
};

RenderState* Renderer_Start();

void Renderer_Update(RenderState* renderState);