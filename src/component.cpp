#include "component.h"
#include "rigidbody.h"
#include "component2.h"

Component* Component_GetWithId(
	SwapBackArray* array,
	uint16 gameObjectId,
	uint16* index)
{
	uint16 i = 0;
	if (index == nullptr)
	{
		index = &i;
	}

	for (*index = 0; *index < array->count; *index++)
	{
		Component* comp = (Component*)SwapBackArray_Get(array, *index);
		if (comp->gameObjectId == gameObjectId)
			return comp;
	}

	return nullptr;
}