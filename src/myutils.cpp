#include "myutils.h"

real32 Abs(float x)
{
    return x < 0 ? -x : x;
}

void GenerateSquarePoints(Vector3 points[], real32 size)
{
	points[0] = { -size, -size };

	points[1] = { size, -size };

	points[2] = { size, size };

	points[3] = { -size, size };
}

void GeneratePolyPoints(Vector3 points[], uint8 numberOfPoints, real32 size)
{
    real32 increments = (2 * PI) / numberOfPoints;

    real32 startAngle = 0;
    if (numberOfPoints % 2 == 0)
    {
        startAngle -= increments * 0.5;
        startAngle = Wrap(startAngle, 0, 2*PI);
    }

    for (int i = 0; i < numberOfPoints; i++)
    {
        points[i] = {(real32)(size * cos(startAngle)),
            (real32)(size * sin(startAngle))};

        startAngle -= increments;
        startAngle = Wrap(startAngle, 0, 2 * PI);
    }
}

Vector3 TransformGetForward(Transform transform)
{
    Vector3 forward = { 0,-1,0 };
    forward = Vector3Transform(
        forward,
        QuaternionToMatrix(transform.rotation));

    return forward;
}