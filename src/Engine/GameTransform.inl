#ifndef ENGINE_GAMETRANSFORM_INL_INCLUDED
#define ENGINE_GAMETRANSFORM_INL_INCLUDED

namespace Engine {


inline GameObject const& GameTransform::GetOwner() const { return *m_pOwner; }
inline Vector3f const& GameTransform::GetPosition() const { return m_position; }
inline Quaternion const& GameTransform::GetRotation() const { return m_rotationQuaternion; }
inline Vector3f const& GameTransform::GetRight() const { return m_right; }
inline Vector3f const& GameTransform::GetUp() const { return m_up; }
inline Vector3f const& GameTransform::GetForward() const { return m_forward; }
inline Vector3f const& GameTransform::GetScale() const { return m_scale; }
inline Matrix4x4 const& GameTransform::GetWorldMatrix() const { return m_worldMatrix; }

inline GameObject& GameTransform::GetOwner() { return *m_pOwner; }

inline void GameTransform::UpdateWorldMatrixFromMatrices() { m_worldMatrix = m_worldRotationMatrix * m_worldScaleMatrix * m_worldPositionMatrix; }


}

#endif