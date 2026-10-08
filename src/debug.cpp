#include "debug.h"

string Vector3String(Vector3 v)
{
	return "{" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z) + "}";;
}

void DrawColliders(PhysicsState* physicsState)
{
    for (int x = 0; x < physicsState->dynamics.size(); x++)
    {
        RigidBody* rb = &physicsState->dynamics[x];

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