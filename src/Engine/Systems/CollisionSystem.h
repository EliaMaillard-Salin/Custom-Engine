#ifndef ENGINE_COLLISIONSYSTEM_H_INCLUDED
#define ENGINE_COLLISIONSYSTEM_H_INCLUDED

#include <array>
#include <vector>

#include "define.h"

namespace Engine { struct SphereCollider; }
namespace Engine { struct BoxCollider; }


namespace Engine { class CollisionSystem; }
class Engine::CollisionSystem
{
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void HandleCollisions();

    [[nodiscard]] bool CheckCollision( SphereCollider const& sphere1, SphereCollider const& sphere2 ) const;
    [[nodiscard]] bool CheckCollision( BoxCollider const& box1, BoxCollider const& box2 ) const;
    [[nodiscard]] bool CheckCollision( SphereCollider const& sphere, BoxCollider const& box ) const;

    std::vector<SphereCollider*> m_sphereColliders;
    std::vector<BoxCollider*>    m_boxColliders;
    // std::array<std::vector<SphereCollider*>, COLLISION_LAYER_COUNT> m_sphereColliders; // Array of vector of SphereCollider Components based on their collision layers.
    // std::array<std::vector<BoxCollider*>, COLLISION_LAYER_COUNT> m_boxColliders;       // Array of vector of BoxCollider Components based on their collision layers.

    friend class Scene;
    friend class GameManager;
};


#endif