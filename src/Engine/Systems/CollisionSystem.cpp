#include "pch.h"
#include "CollisionSystem.h"

#include "Components/SphereCollider.h"
#include "Components/BoxCollider.h"

#include "GameObject.h"

namespace Engine {


void CollisionSystem::HandleCollisions()
{
    for ( auto sphere1 = m_sphereColliders.begin(); sphere1 != m_sphereColliders.end(); ++sphere1 )
    {
        for ( auto sphere2 = sphere1+1; sphere2 != m_sphereColliders.end(); ++sphere2 )
        {
            if ( CheckCollision( **sphere1, **sphere2 ) == false ) continue;

            // Handle Collision Here (Sphere & Sphere)
            (*sphere1)->m_colliding = true;
            (*sphere2)->m_colliding = true;
        }

        for ( auto box1 = m_boxColliders.begin(); box1 != m_boxColliders.end(); ++box1 )
        {
            if ( CheckCollision( **sphere1, **box1 ) == false ) continue;

            // Handle Collision Here (Sphere & Box)
            (*sphere1)->m_colliding = true;
            (*box1)->m_colliding = true;
        }
    }

    for ( auto box1 = m_boxColliders.begin(); box1 != m_boxColliders.end(); ++box1 )
    {
        for ( auto box2 = box1+1; box2 != m_boxColliders.end(); ++box2 )
        {
            if ( CheckCollision( **box1, **box2 ) == false ) continue;

            // Handle Collision Here (Box & Box)
            (*box1)->m_colliding = true;
            (*box2)->m_colliding = true;
        }
    }
}


bool CollisionSystem::CheckCollision( SphereCollider const& sphere1, SphereCollider const& sphere2 ) const
{
    Vector3f const& position1 = sphere1.offset + sphere1.m_pOwner->transform.GetPosition();
    Vector3f const& position2 = sphere2.offset + sphere2.m_pOwner->transform.GetPosition();

    float32 const radius1 = sphere1.scale * sphere1.m_pOwner->transform.GetScale().x * 0.5f;
    float32 const radius2 = sphere2.scale * sphere2.m_pOwner->transform.GetScale().x * 0.5f;

    float32 const distanceSquared = position1.DistanceToSquared( position2 );
    float32 const combinedRadiusSquared = ( radius1 + radius2 ) * ( radius1 + radius2 );

    return distanceSquared <= combinedRadiusSquared;
}

bool CollisionSystem::CheckCollision( BoxCollider const& box1, BoxCollider const& box2 ) const
{
    Vector3f const& position1 = box1.offset + box1.m_pOwner->transform.GetPosition();
    Vector3f const& position2 = box2.offset + box2.m_pOwner->transform.GetPosition();

    Vector3f const& halfSize1 = box1.scale * box1.m_pOwner->transform.GetScale() * 0.5f;
    Vector3f const topLeft1 = position1 - halfSize1;
    Vector3f const bottomRight1 = position1 + halfSize1;

    Vector3f const& halfSize2 = box2.scale * box2.m_pOwner->transform.GetScale() * 0.5f;
    Vector3f const topLeft2 = position2 - halfSize2;
    Vector3f const bottomRight2 = position2 + halfSize2;

    return topLeft1.x <= bottomRight2.x && topLeft2.x <= bottomRight1.x &&
            topLeft1.y <= bottomRight2.y && topLeft2.y <= bottomRight1.y &&
             topLeft1.z <= bottomRight2.z && topLeft2.z <= bottomRight1.z;
}

bool CollisionSystem::CheckCollision( SphereCollider const& sphere, BoxCollider const& box ) const
{
    Vector3f const& positionSphere = sphere.offset + sphere.m_pOwner->transform.GetPosition();
    Vector3f const& positionBox = box.offset + box.m_pOwner->transform.GetPosition();

    float32 const radiusSphere = sphere.scale * sphere.m_pOwner->transform.GetScale().x * 0.5f;

    Vector3f const& halfSizeBox = box.scale * box.m_pOwner->transform.GetScale() * 0.5f;
    Vector3f const topLeftBox = positionBox - halfSizeBox;
    Vector3f const bottomRightBox = positionBox + halfSizeBox;

    Vector3f const collisionPoint {
        positionSphere.x < topLeftBox.x ? topLeftBox.x : positionSphere.x > bottomRightBox.x ? bottomRightBox.x : positionSphere.x,
        positionSphere.y < topLeftBox.y ? topLeftBox.y : positionSphere.y > bottomRightBox.y ? bottomRightBox.y : positionSphere.y,
        positionSphere.z < topLeftBox.z ? topLeftBox.z : positionSphere.z > bottomRightBox.z ? bottomRightBox.z : positionSphere.z
    };

    float32 const distanceSquared = positionSphere.DistanceToSquared( collisionPoint );
    float32 const radiusSphereSquared = radiusSphere * radiusSphere;

    return distanceSquared <= radiusSphereSquared;
}


}
