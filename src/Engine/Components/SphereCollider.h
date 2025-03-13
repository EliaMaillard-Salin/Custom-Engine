#ifndef ENGINE_SPHERECOLLIDER_H_INCLUDED
#define ENGINE_SPHERECOLLIDER_H_INCLUDED

#include "define.h"

#include "Collider.h"


namespace Engine { struct SphereCollider; }
struct Engine::SphereCollider : Engine::Collider<Component::SphereCollider>
{
    float32 scale = 1.0f; // Collider's scale (separated from its owner's scale).

    friend class CollisionSystem;
};


#endif