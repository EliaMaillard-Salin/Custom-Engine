#include "pch.h"
#include "GameTransform.h"

#include "GameObject.h"

namespace Engine {


GameTransform const GameTransform::Identity {};


void GameTransform::SetPosition( Vector3f const& position )
{
    m_position = position;
    m_dirty = true;
}

void GameTransform::SetRotation( Quaternion const& rotation )
{
    m_rotationQuaternion = rotation;
    m_dirty = true;
}

void GameTransform::SetScale( Vector3f const& scale )
{
    m_scale = scale;
    m_dirty = true;
}


void GameTransform::Translate( Vector3f const& translation )
{
    m_position += translation;
    m_dirty = true;
}

void GameTransform::Rotate( Quaternion const& rotation )
{
    m_rotationQuaternion *= rotation;
    m_dirty = true;
}

void GameTransform::Rotate( float32 const yaw, float32 const pitch, float32 const roll )
{
    Quaternion pitchQuaternion;
    pitchQuaternion.FromAxisAngle( Vector3f::Right, pitch );

    Quaternion yawQuaternion;
    yawQuaternion.FromAxisAngle( Vector3f::Up, yaw );

    Quaternion rollQuaternion;
    rollQuaternion.FromAxisAngle( Vector3f::Forward, roll );

    Quaternion result = rollQuaternion;
    result *= pitchQuaternion;
    result *= yawQuaternion;
    
    m_rotationQuaternion *= result;

    m_dirty = true;
}

void GameTransform::Scale( Vector3f const& scale )
{
    m_scale *= scale;
    m_dirty = true;
}


void GameTransform::UpdateLocalMatrices()
{
    UpdateMatrixFromPosition();
    UpdateMatrixFromQuaternion();
    UpdateVectorsFromMatrix();
    UpdateMatrixFromScale();
}

void GameTransform::UpdateWorldMatrices()
{
    if ( m_pOwner->m_pParent == nullptr )
    {
        m_worldPositionMatrix = m_positionMatrix;
        m_worldRotationMatrix = m_rotationMatrix;
        m_worldScaleMatrix = m_scaleMatrix;
        return;
    }

    GameTransform const& transform = m_pOwner->m_pParent->transform;
    m_worldPositionMatrix = transform.m_worldPositionMatrix * m_positionMatrix;
    m_worldRotationMatrix = transform.m_worldRotationMatrix * m_rotationMatrix;
    m_worldScaleMatrix = transform.m_worldScaleMatrix * m_scaleMatrix;
}


}