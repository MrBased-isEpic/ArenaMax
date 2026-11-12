#include "physics.h"
#include "gameObject.h"
#include "gamestate.h"

PhysicsState* Physics_Start()
{
	PhysicsState* physicState = new PhysicsState;
	physicState->dynamics = SwapBackArray_Create(sizeof(RigidBody), 5);
	return physicState;
}

RigidBody* Physics_GetRigidBody(PhysicsState* physicsState, uint16 gameObjectId, uint16* index)
{
	return (RigidBody*)Component_GetWithId(&physicsState->dynamics, gameObjectId, index);
}

Vector3 perp(Vector3 v)
{
	return {v.y, -v.x, v.z};
}

void Rigidbody_GetNormals(
	RigidBody* rigidBody)
{
	Vector3 points[5];
	uint8 noOfPoints = rigidBody->numberOfPoints;

	for (int i = 0; i < noOfPoints; i++)
	{
		points[i] = rigidBody->points[i];
	}

	for (int i = 0; i < noOfPoints; i++)
	{
		Vector3 edge = Vector3Subtract(points[(i+1) % noOfPoints], points[i]);

		rigidBody->normals[i] = Vector3Normalize(perp(edge));
	}
}

bool Physics_GetCollision(
	PhysicsState* physicsState,
	RigidBody* rb,
	Collision* col)
{
	for (int i = 0; i < physicsState->collisions.size(); i++)
	{
		Collision collision = physicsState->collisions[i];

		if (collision.self == rb)
		{
			*col = collision;
			return true;
		}
	}
	return false;
}


void Physics_UpdateCollisions(PhysicsState* physicsState)
{
	// Clear All Previous Collision Reports
	physicsState->collisions.clear();

	//Collision Checks
	for (int x = 0; x < physicsState->dynamics.count - 1; x++) // cycle thru rigidbody
	{
		//cout << endl << "Checking collision for rigidbody : " << x << endl;
		RigidBody* rb = (RigidBody*)SwapBackArray_Get(&physicsState->dynamics, x);

		if (rb->isStatic) continue;

		// cycle thru other rigidbodies
		for (int y = 0; y < physicsState->dynamics.count; y++)
		{
			if (rb == 
				(RigidBody*)SwapBackArray_Get(&physicsState->dynamics, y))
			{
				continue;
			}

			RigidBody* rb2 = (RigidBody*)SwapBackArray_Get(&physicsState->dynamics, y);

			Vector3 axes[10];

			int noOfPoints1 = rb->numberOfPoints == 1 ? 0 : rb->numberOfPoints;
			int noOfPoints2 = rb2->numberOfPoints == 1 ? 0 : rb2->numberOfPoints;

			uint8 axesCount = noOfPoints1 + noOfPoints2;

			for (int z = 0; z < noOfPoints1; z++)
			{
				axes[z] = rb->normals[z];
			}

			for (int z = noOfPoints1; z < axesCount; z++)
			{
				axes[z] = rb2->normals[z - noOfPoints1];
			}

			bool intersecting = false;
			real32 minimumTranslation = FLT_MAX;
			uint8 mtIndex = 0;

			for (int j = 0; j < axesCount; j++) // cycle thru axes
			{
				Vector3 axis = axes[j];

				// Find min and max along axis
				real32 amin = FLT_MAX, amax = -FLT_MAX;
				for (int i = 0; i < rb->numberOfPoints; i++)
				{
					Vector3 projected = Vector3Project(rb->points[i], axis);
					real32 dot = Vector3DotProduct(projected, axis);

					if (dot < amin)
					{
						amin = dot;
					}

					if (dot > amax)
					{
						amax = dot;
					}
				}
				if (noOfPoints1 == 0)
				{
					amin -= rb->points[1].x;
					amax += rb->points[1].x;
				}

				real32 bmin = FLT_MAX, bmax = -FLT_MAX;
				for (int i = 0; i < noOfPoints2; i++)
				{
					Vector3 projected = Vector3Project(rb2->points[i], axis);
					real32 dot = Vector3DotProduct(projected, axis);

					if (dot < bmin)
					{
						bmin = dot;
					}

					if (dot > bmax)
					{
						bmax = dot;
					}
				}
				if (noOfPoints2 == 0)
				{
					bmin -= rb2->points[1].x;
					bmax += rb2->points[1].x;
				}

				// Check if it's intersecting on this axis
				intersecting = (amin <= bmax) && (amax >= bmin);

				if (!intersecting) break;

				if (minimumTranslation > amax - bmin)
				{
					minimumTranslation = amax - bmin;
					mtIndex = j;
				}
			}

			if (intersecting)
			{
				Collision collision = {};

				collision.self = rb;
				collision.other = rb2;

				collision.mtv = Vector3Scale(axes[mtIndex], minimumTranslation);

				physicsState->collisions.push_back(collision);
			}
		}
	}
}

void Physics_ResolveCollisions(PhysicsState* physicsState)
{
	for (int i = 0; i < physicsState->collisions.size(); i++)
	{
		Collision collision = physicsState->collisions[i];

		RigidBody* rigidbody = collision.self;

		Vector3 colDir = Vector3Negate(Vector3Normalize(collision.mtv));
		real32 projection = Vector3DotProduct(rigidbody->velocity, colDir);

		Vector3 negationVector = Vector3Negate(Vector3Scale(colDir, projection));

		Vector3 newVelocity =
			rigidbody->velocity - Vector3Scale(colDir, projection);

		newVelocity = newVelocity -
			Vector3Scale(Vector3Scale(colDir, projection), rigidbody->bounce);

		rigidbody->velocity = newVelocity;

		Transform* transform = &rigidbody->component.gameObject->transform;

		transform->translation =
				Vector3Subtract(transform->translation, collision.mtv);

		for (int j = 0; j < rigidbody->numberOfPoints; j++)
		{
			rigidbody->points[j] = 
				Vector3Subtract(rigidbody->points[j], collision.mtv);
		}
	}
}

void Physics_Update(PhysicsState* physicsState, real32 timeStep)
{
	Physics_ResolveCollisions(physicsState);

	for (int x = 0; x < physicsState->dynamics.count; x++)
	{
		//cout << x << endl;
		RigidBody* rb = (RigidBody*)SwapBackArray_Get(&physicsState->dynamics, x);

		RigidBody_Update(rb, timeStep);
	}

	Physics_UpdateCollisions(physicsState);
}