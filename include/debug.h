#pragma once

#include "raylib.h"
#include <string>
#include <iostream>
#include "physics.h"

using namespace std;

string Vector3String(Vector3 v);

void DrawColliders(PhysicsState* physicsState);