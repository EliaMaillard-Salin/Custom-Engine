#ifndef MATH_TRANSFORM_H_INCLUDED
#define MATH_TRANSFORM_H_INCLUDED
#include "Vector3.hpp"
#include "Quaternion.h"
#include "Matrix4x4.hpp"


struct Transform
{
    static Transform const Identity;
    void SetIdentity();
    
    //Position
    Vector3f  m_position       = Vector3f::Zero;      // Transform's position (local).
    Matrix4x4 m_positionMatrix = Matrix4x4::Identity; // Transform's matrix containing its position (local).

    //Rotation
    Vector3f   m_right              = Vector3f::Right;      // Transform's right vector (local).
    Vector3f   m_up                 = Vector3f::Up;         // Transform's up vector (local).
    Vector3f   m_forward            = Vector3f::Forward;    // Transform's forward vector (local).
    Quaternion m_rotationQuaternion = Quaternion::Identity; // Transform's quaternion representing its rotation (local).
    Matrix4x4  m_rotationMatrix     = Matrix4x4::Identity;  // Transform's matrix containing its rotation (local).

    //Scale
    Vector3f  m_scale       = Vector3f::One;       // Transform's scale (local).
    Matrix4x4 m_scaleMatrix = Matrix4x4::Identity; // Transform's matrix containing its scale (local).

protected:
    void UpdateMatrixFromPosition();
    void UpdateMatrixFromQuaternion();
    void UpdateVectorsFromMatrix();
    void UpdateMatrixFromScale();
};


#endif

