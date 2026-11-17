#pragma once

#include "raylib.h"
#include <string>
#include <iostream>
#include "arrays.h"

using namespace std;

struct PhysicsState;

string Vector3String(Vector3 v);

void DrawColliders(PhysicsState* physicsState);


void log(const char* file, uint16 line, const char* message);
#define Log(msg) log(__FILE__, __LINE__, msg);

void logError(const char* file, uint16 line, const char* message);
#define LogError(msg) logError(__FILE__, __LINE__, msg);