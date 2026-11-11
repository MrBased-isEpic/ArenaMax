#pragma once

#include "types.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

struct SwapBackArray
{
	uint8* start;
	uint16 elementSize = 0;
	uint16 count = 0;
	uint16 capacity = 0;
};

SwapBackArray SwapBackArray_Create(
	uint16 elementSize,
	uint16 capacity,
	void* address = nullptr);

void SwapBackArray_Destroy(SwapBackArray* array);

uint16 SwapBackArray_GetSize(SwapBackArray* array);

void SwapBackArray_Relocate(SwapBackArray* array, void* newAddress, uint16 newcapacity = 0);

void SwapBackArray_Add(
	SwapBackArray* array,
	const void* element);

void SwapBackArray_Remove(
	SwapBackArray* array,
	uint16 index);

void* SwapBackArray_Get(
	const SwapBackArray* array,
	uint16 index);

void* SwapBackArray_Last(const SwapBackArray* array);

//LINEAR ALLOCATOR

struct LinearAllocator
{
	uint8* start = nullptr;
	uint8* end = nullptr;

	uint16 capacity = 0;
};

LinearAllocator LinearAllocator_Create(uint16 size);

uint16 LinearAllocator_Size(const LinearAllocator* linalloc);

void* LinearAllocator_Push(LinearAllocator* linalloc, uint16 size);

void LinearAllocator_Clear(LinearAllocator* linalloc);

void LinearAllocator_Delete(LinearAllocator* linalloc);