#include "input.h"

void Input_Get(Input* input)
{
    *input = {};

    if (IsKeyDown(KEY_W))
    {
        input->forward = true;
    }

    if (IsKeyDown(KEY_A))
    {
        input->left = true;
    }

    if (IsKeyDown(KEY_D))
    {
        input->right = true;
    }
}