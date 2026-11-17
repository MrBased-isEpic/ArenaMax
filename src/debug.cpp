#include "debug.h"
#include "physics.h"

string Vector3String(Vector3 v)
{
	return "{" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z) + "}";;
}

void DrawColliders(PhysicsState* physicsState)
{
    for (int x = 0; x < physicsState->dynamics.count; x++)
    {
        RigidBody* rb = (RigidBody*)SwapBackArray_Get(&physicsState->dynamics, x);

        if (rb->numberOfPoints == 1)
        {
            DrawCircleLines(rb->points[0].x, rb->points[0].y,
                rb->points[1].x, ORANGE);

            continue;
        }

        for (int i = 0; i < rb->numberOfPoints; i++)
        {
            DrawLine3D(rb->points[i], rb->points[(i + 1) % rb->numberOfPoints], ORANGE);
        }
    }
}

void SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}

// Function to reset the console color
void ResetColor() { cout << "\033[0m"; }

void log(const char* file, uint16 line, const char* message)
{
    cout << file << "("<< line << "): LOG: " << message << endl;
}

void logError(const char* file, uint16 line, const char* message)
{
    SetColor(91);
    cout << file << "(" << line << "): ERROR: " << message << endl;
    ResetColor();
}