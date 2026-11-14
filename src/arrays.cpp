#include "arrays.h"

SwapBackArray SwapBackArray_Create(
	uint16 elementSize,
	uint16 capacity,
	void* address)
{
	SwapBackArray array = {};
	array.elementSize = elementSize;
	array.capacity = capacity;

	if (address == nullptr)
	{
		array.start = (uint8*)malloc(elementSize * capacity);
	}
	else
	{
		array.start = (uint8*)address;
	}

	return array;
}

void SwapBackArray_Destroy(SwapBackArray* array)
{
	free(array->start);
	array->start = nullptr;
	return;
}

uint16 SwapBackArray_GetSize(SwapBackArray* array)
{
	return array->count * array->elementSize;
}

void SwapBackArray_Relocate(SwapBackArray* array, void* newAddress, uint16 newcapacity)
{
	memcpy(newAddress,
		(void*)array->start,
		SwapBackArray_GetSize(array));

	array->start = (uint8*)newAddress;
	if (newcapacity > 0)
	{
		array->capacity = newcapacity;
	}
}

void SwapBackArray_Add(
	SwapBackArray* array,
	const void* element)
{
	if (array->count == array->capacity) return;

	memcpy((void*)(array->start + (array->elementSize * array->count)),
		element,
		array->elementSize);

	array->count++;
}

void SwapBackArray_Remove(
	SwapBackArray* array,
	uint16 index)
{
	if (array->count == 0) return;
	if (array->count <= index) return;

	if (index == array->count - 1) // removing last element
	{
		array->count--;
		return;
	}

	memcpy((void*)(array->start + (array->elementSize * index)),
		(void*)(array->start + (array->elementSize * array->count - 1)),
		array->elementSize);

	array->count--;
}

void* SwapBackArray_Get(
	const SwapBackArray* array,
	uint16 index)
{
	return array->start + (array->elementSize * index);
}

void* SwapBackArray_Last(const SwapBackArray* array)
{
	return array->start + (array->elementSize * (array->count-1));
}

// LINEAR ALLOCATOR

LinearAllocator LinearAllocator_Create(uint16 size)
{
	LinearAllocator linalloc = {};

	linalloc.start = (uint8*)malloc(size);
	linalloc.capacity = size;

	linalloc.end = linalloc.start;

	return linalloc;
}

uint16 LinearAllocator_Size(LinearAllocator* linalloc)
{
	return (uint16)(linalloc->end - linalloc->start);
}

void* LinearAllocator_Push(LinearAllocator* linalloc, uint16 size)
{
	if (LinearAllocator_Size(linalloc) > linalloc->capacity)
	{
		std::cout << "memory overflow detected, returning null" << std::endl;
		return nullptr;
	}

	linalloc->capacity += size;
	void* returnPtr = linalloc->end;
	linalloc->end += size;
	return returnPtr;
}

void LinearAllocator_Clear(LinearAllocator* linalloc)
{
	linalloc->end = linalloc->start;
}

void LinearAllocator_Delete(LinearAllocator* linalloc)
{
	free(linalloc->start);

	linalloc->start = nullptr;
	linalloc->end = nullptr;
}