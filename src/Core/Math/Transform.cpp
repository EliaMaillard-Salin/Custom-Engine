#include "Transform.h"


void Transform::SetIdentity()
{
    m_position       = Vector3f::Zero;
    m_positionMatrix = Matrix4x4::Identity;

    m_right              = Vector3f::Right;
    m_up                 = Vector3f::Up;
    m_forward            = Vector3f::Forward;
    m_rotationQuaternion = Quaternion::Identity;
    m_rotationMatrix     = Matrix4x4::Identity;

    m_scale       = Vector3f::One;
    m_scaleMatrix = Matrix4x4::Identity;
}


void Transform::UpdateMatrixFromPosition()
{
    m_positionMatrix.values[3][0] = m_position.x;
    m_positionMatrix.values[3][1] = m_position.y;
    m_positionMatrix.values[3][2] = m_position.z;
}

void Transform::UpdateMatrixFromQuaternion()
{
    float32 const xx = m_rotationQuaternion.x * m_rotationQuaternion.x;
    float32 const yy = m_rotationQuaternion.y * m_rotationQuaternion.y;
    float32 const zz = m_rotationQuaternion.z * m_rotationQuaternion.z;
    float32 const ww = m_rotationQuaternion.w * m_rotationQuaternion.w;

    float32 const xy = m_rotationQuaternion.x * m_rotationQuaternion.y;
    float32 const xz = m_rotationQuaternion.x * m_rotationQuaternion.z;
    float32 const xw = m_rotationQuaternion.x * m_rotationQuaternion.w;

    float32 const yz = m_rotationQuaternion.y * m_rotationQuaternion.z;
    float32 const yw = m_rotationQuaternion.y * m_rotationQuaternion.w;

    float32 const zw = m_rotationQuaternion.z * m_rotationQuaternion.w;

    // m_rotationMatrix.values[0][0] = xx + yy - zz - ww; //
    m_rotationMatrix.values[0][0] = 1.0f - 2.0f * ( zz + ww );
    m_rotationMatrix.values[0][1] = 2.0f * ( yz - xw );
    m_rotationMatrix.values[0][2] = 2.0f * ( yw + xz );
    m_rotationMatrix.values[0][3] = 0.0f;
    
    m_rotationMatrix.values[1][0] = 2.0f * ( yz + xw );
    // m_rotationMatrix.values[1][1] = xx - yy + zz - ww; //
    m_rotationMatrix.values[1][1] = 1.0f - 2.0f * ( yy + ww );
    m_rotationMatrix.values[1][2] = 2.0f * ( zw - xy );
    m_rotationMatrix.values[1][3] = 0.0f;
    
    m_rotationMatrix.values[2][0] = 2.0f * ( yw - xz );
    m_rotationMatrix.values[2][1] = 2.0f * ( zw + xy );
    // m_rotationMatrix.values[2][2] = xx - yy - zz + ww; //
    m_rotationMatrix.values[2][2] = 1.0f - 2.0f * ( yy + zz );
    m_rotationMatrix.values[2][3] = 0.0f;

    m_rotationMatrix.values[3][0] = 0.0f;
    m_rotationMatrix.values[3][1] = 0.0f;
    m_rotationMatrix.values[3][2] = 0.0f;
    m_rotationMatrix.values[3][3] = 1.0f;
}

void Transform::UpdateVectorsFromMatrix()
{
    m_right.x = m_rotationMatrix.values[0][0];
    m_right.y = m_rotationMatrix.values[0][1];
    m_right.z = m_rotationMatrix.values[0][2];
    
    m_up.x = m_rotationMatrix.values[1][0];
    m_up.y = m_rotationMatrix.values[1][1];
    m_up.z = m_rotationMatrix.values[1][2];

    m_forward.x = m_rotationMatrix.values[2][0];
    m_forward.y = m_rotationMatrix.values[2][1];
    m_forward.z = m_rotationMatrix.values[2][2];
}

void Transform::UpdateMatrixFromScale()
{
    m_scaleMatrix.values[0][0] = m_scale.x;
    m_scaleMatrix.values[1][1] = m_scale.y;
    m_scaleMatrix.values[2][2] = m_scale.z;
}