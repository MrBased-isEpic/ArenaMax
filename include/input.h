#pragma once
#include "types.h"
#include "raylib.h"

struct Input
{
    bool8 forward;
    bool8 left;
    bool8 right;
};

void Input_Get(Input* input);