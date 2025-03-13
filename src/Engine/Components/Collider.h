#ifndef ENGINE_COLLIDER_H_INCLUDED
#define ENGINE_COLLIDER_H_INCLUDED

#include "define.h"

#include "Math/Vector3.hpp"

#include "ComponentBase.h"


namespace Engine { template <uint16 T> struct Collider; }
template <uint16 T>
struct Engine::Collider : Engine::ComponentBase<T>
{
    char const* tag = nullptr; // Collider's tag (used for identification when colliding).
    uint8 collisionLayer = 0;  // Collider's collision layer (used to specify which colliders it can collide with).

    Vector3f offset = Vector3f::Zero; // Collider's offset (separated from its owner's position).
    
    bool m_colliding = false;
};


#endif