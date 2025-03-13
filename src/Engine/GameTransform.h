#ifndef ENGINE_GAMETRANSFORM_H_INCLUDED
#define ENGINE_GAMETRANSFORM_H_INCLUDED

#include "Math/Matrix4x4.hpp"
#include "Math/Transform.h"

namespace Engine { class GameObject; }


namespace Engine { class GameTransform; }
class Engine::GameTransform : Transform
{
public:
    static GameTransform const Identity;

    GameTransform() { SetIdentity(); }
    ~GameTransform() = default;
    
    [[nodiscard]] GameObject const& GetOwner() const;
    [[nodiscard]] Vector3f const& GetPosition() const;
    [[nodiscard]] Quaternion const& GetRotation() const;
    [[nodiscard]] Vector3f const& GetRight() const;
    [[nodiscard]] Vector3f const& GetUp() const;
    [[nodiscard]] Vector3f const& GetForward() const;
    [[nodiscard]] Vector3f const& GetScale() const;
    [[nodiscard]] Matrix4x4 const& GetWorldMatrix() const;

    [[nodiscard]] GameObject& GetOwner();
    
    void SetPosition( Vector3f const& position );
    void SetRotation( Quaternion const& rotation );
    void SetScale( Vector3f const& scale );
    
    void Translate( Vector3f const& translation );
    void Rotate( Quaternion const& rotation );
    void Rotate( float32 yaw, float32 pitch, float32 roll );
    void Scale( Vector3f const& scale );

    void UpdateMatrix();

private:
    void UpdateLocalMatrices();
    void UpdateWorldMatrices();
    void UpdateWorldMatrixFromMatrices();
    
    GameObject* m_pOwner = nullptr; // Pointer to the Transform's GameObject

    // Position
    using Transform::m_position;
    using Transform::m_positionMatrix;
    Matrix4x4 m_worldPositionMatrix = Matrix4x4::Identity; // Transform's matrix containing its position (world)

    // Rotation
    using Transform::m_right;
    using Transform::m_up;
    using Transform::m_forward;
    using Transform::m_rotationQuaternion;
    using Transform::m_rotationMatrix;
    Matrix4x4 m_worldRotationMatrix = Matrix4x4::Identity; // Transform's matrix containing its rotation (world)

    // Scale
    using Transform::m_scale;
    using Transform::m_scaleMatrix;
    Matrix4x4 m_worldScaleMatrix = Matrix4x4::Identity; // Transform's matrix containing its scale (world)

    // World Matrix
    Matrix4x4 m_worldMatrix = Matrix4x4::Identity; // Transform's matrix containing its position, rotation and scale (world)

    bool m_dirty = true; // Indicates whether the matrices need to be recalculated

    friend class GameObject;
    friend class Scene;
};


#include "GameTransform.inl"

#endif