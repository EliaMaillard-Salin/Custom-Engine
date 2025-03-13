#include "pch.h"
#include "RigidBody.h"

void Engine::RigidBody::ApplyForces( float32 x,float32 y,float32 z )
{
	appliedforces.x += x;
	appliedforces.y += y;
	appliedforces.z += z;
}

void Engine::RigidBody::ApplyForces( Vector3f force )
{
	ApplyForces( force.x,force.y,force.z );
}
