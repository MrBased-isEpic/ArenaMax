#pragma once

#include "types.h"
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
	uint16 capacity);

void SwapBackArray_Destroy(const SwapBackArray* array);

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