#ifndef ENGINE_BOXCOLLIDER_H_INCLUDED
#define ENGINE_BOXCOLLIDER_H_INCLUDED

#include "define.h"

#include "Collider.h"


namespace Engine { struct BoxCollider; }
struct Engine::BoxCollider : Engine::Collider<Component::BoxCollider>
{
    Vector3f scale = Vector3f::One; // Collider's scale (separated from its owner's scale).

    friend class CollisionSystem;
};


#endif