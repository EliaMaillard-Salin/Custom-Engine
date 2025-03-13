#include "pch.h"

#include "Components/RigidBody.h"

#include "GameObject.h"

#include "PhysicsSystem.h"
#include "GameManager.h"


namespace Engine

{

	PhysicsSystem::PhysicsSystem() : 
		m_objectWithGravity(std::vector<RigidBody*>()),
		m_pRigidBodys(new std::vector<RigidBody*>())
	{}



	void PhysicsSystem::HandlePhysics()
	{
		// Gravity between objects
		for (RigidBody* pRigidBody : *m_pRigidBodys)
		{
			for (RigidBody* pGravity : m_objectWithGravity)
			{
				if (pRigidBody != pGravity && pRigidBody->takesGravity == true)
				{
					float32 distanceBetweenSquared = pRigidBody->centerOfMass.DistanceToSquared(pGravity->centerOfMass);
					float32 mass = pRigidBody->mass * pGravity->mass;
					float32 m_forcedegravité = GRAVITY_CONSTANT * (mass / distanceBetweenSquared);

					Vector3f direction;

					direction.x = pGravity->centerOfMass.x - pRigidBody->centerOfMass.x;
					direction.y = pGravity->centerOfMass.y - pRigidBody->centerOfMass.y;
					direction.z = pGravity->centerOfMass.z - pRigidBody->centerOfMass.z;

					direction.Normalize();

					direction *= m_forcedegravité;

					pRigidBody->appliedforces += direction;
				}
			}
			pRigidBody->acceleration = pRigidBody->appliedforces * (1 / pRigidBody->mass);

			pRigidBody->velocity += pRigidBody->acceleration;
			pRigidBody->GetOwner().transform.Translate(pRigidBody->velocity * GameManager::GetFixedDeltaTime());
			pRigidBody->centerOfMass = pRigidBody->GetOwner().transform.GetPosition();

			pRigidBody->acceleration = Vector3f::Zero;
			pRigidBody->appliedforces = Vector3f::Zero;
		}
	}

	void PhysicsSystem::ApplyForce(RigidBody* pRigidBody, float32 x, float32 y, float32 z)
	{
		pRigidBody->appliedforces += Vector3f(x, y, z);
	}

}