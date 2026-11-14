#include "render.h"
#include "polyrendererform.h"

RenderState* Renderer_Start()
{
	RenderState* renderState = new RenderState;
	//renderState->shapes.reserve(5);
 	renderState->polys = SwapBackArray_Create(sizeof(PolyRenderer), 5);

	return renderState;
}

void Renderer_Update(RenderState* renderState)
{
	for (int i = 0; i < renderState->polys.count; i++)
	{
		PolyRenderer* sr = (PolyRenderer*)SwapBackArray_Get(&renderState->polys, i);
		Transform transform = *sr->transform;

		DrawPoly(
			transform.translation.xy,
			sr->noOfSides,
			sr->size,
			(QuaternionToEuler(transform.rotation).z *
				RAD2DEG) + sr->rotationOffset,
			sr->color);
	}
}

Component* Polyrenderer_Create(
	ComponentForm* form,
	GameState* gameState,
	GameObject* gameObject)
{
	RenderState* renderState = gameState->renderState;
	PolyrendererForm* pForm = (PolyrendererForm*)form;
	PolyRenderer r = {};

	r.noOfSides = pForm->noOfSides;
	r.size = pForm->radius;
	r.color = pForm->color;
	r.rotationOffset = pForm->rotationOffset;

	r.component.gameObjectId = gameObject->id;
	r.transform = &gameObject->transform;

	SwapBackArray_Add(&renderState->polys, &r);

	return (Component*)SwapBackArray_Last(&renderState->polys);
}

void PolyRenderer_InitReferences(
	Component* component,
	GameObject* gameObject)
{
	PolyRenderer* r = (PolyRenderer*)component;
	r->transform = &gameObject->transform;
}

void PolyRenderer_Delete(
	Component* component,
	GameState* gameState)
{
	PolyRenderer* polyRenderer = (PolyRenderer*)component;
	RenderState* renderState = gameState->renderState;

	GameObject_RemoveComponentReference(
		polyRenderer->component.gameObject,
		(Component*)polyRenderer);

	uint16 index;

	Component_GetWithId(&renderState->polys, polyRenderer->component.gameObjectId, &index);
	SwapBackArray_Remove(&renderState->polys, index);

	GameObject_SetComponentReference(
		polyRenderer->component.gameObject,
		(Component*)polyRenderer);
}

ComponentForm* PolyRenderer_GetForm(Component* component)
{
	PolyRenderer* poly = (PolyRenderer*)component;
	PolyrendererForm* pForm = (PolyrendererForm*)malloc(sizeof(PolyrendererForm));

	pForm->noOfSides = poly->noOfSides;
	pForm->radius = poly->size;
	pForm->color = poly->color;
	pForm->rotationOffset = poly->rotationOffset;

	return (ComponentForm*)pForm;
}

//uint16 ShapeRenderer_Create(
//	RenderState* renderState,
//	Transform* transform,
//	PolyRenderer** shapeRenderer,
//	uint8 numberOfSides,
//	real32 size,
//	Color color)
//{
//	PolyRenderer sr = {};
//	sr.component.type = POLYRENDERER;
//	sr.noOfSides = numberOfSides;
//	sr.size = size;
//	sr.color = color;
//	sr.rotationOffset = 0;
//
//	sr.transform = transform;
//
//	sr.component.id = renderState->rendererIdCount++;
//
//	renderState->shapes.push_back(sr);
//
//	*shapeRenderer = &renderState->shapes.back();
//
//	return sr.component.id;
//}