#pragma once

#include "define.h"

#include "ComponentBase.h"
#include "Math/Vector3.hpp"

namespace Engine { class PhysicsSystem; }

namespace Engine { struct RigidBody; }
struct Engine::RigidBody : Engine::ComponentBase<Component::RigidBody>
{
	void ApplyForces( float32 x,float32 y,float32 z );
	void ApplyForces( Vector3f force );


	float32 mass = 1.0f; // Volume * density
	Vector3f centerOfMass = Vector3f(0.0f, 0.0f, 0.0f);
	
	Vector3f velocity = Vector3f(0.0f,0.0f,0.0f);
	Vector3f acceleration = Vector3f(0.0f, 0.0f, 0.0f);
	Vector3f direction = Vector3f(0.0f, 0.0f, 0.0f);

	bool takesGravity = true;

private:
	Vector3f appliedforces = Vector3f(0.0f, 0.0f, 0.0f);


	friend PhysicsSystem;
};

