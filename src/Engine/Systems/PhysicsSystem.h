#ifndef ENGINE_PHYSICSSYSTEM_H_INCLUDED
#define ENGINE_PHYSICSSYSTEM_H_INCLUDED

#include <vector>
#include "define.h"

#define GRAVITY_CONSTANT (float32)0.000000000066674f

namespace Engine { struct RigidBody; }


namespace Engine { class PhysicsSystem; }
class Engine::PhysicsSystem
{

    PhysicsSystem();
    ~PhysicsSystem() = default;

    void HandlePhysics();

    void ApplyForce(RigidBody* pRigidBody, float32 x,float32 y,float32 z);

    void HandleOrbit(RigidBody* pOrbiter);

    std::vector<RigidBody*> m_objectWithGravity = {};

    std::vector<RigidBody*>* m_pRigidBodys = nullptr;

    friend class Scene;
    friend class GameManager;
};


#endif