#ifndef MATH_QUATERNION_H_INCLUDED
#define MATH_QUATERNION_H_INCLUDED

#include "define.h"


struct Quaternion
{
    float32 x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

    static Quaternion const Null;
    static Quaternion const Identity;

    Quaternion() = default;
    explicit Quaternion( float32 x, float32 y, float32 z, float32 w );
    Quaternion( Quaternion const& other ) = default;
    ~Quaternion() = default;

    Quaternion& operator=( Quaternion const& other );

    [[nodiscard]] bool IsNull() const;
    [[nodiscard]] bool IsIdentity() const;

    void FromAxisAngle( Vector3f const& axis, float32 angle );

    [[nodiscard]] Quaternion operator+( Quaternion const& other ) const;
    [[nodiscard]] Quaternion operator-( Quaternion const& other ) const;
    [[nodiscard]] Quaternion operator*( Quaternion const& other ) const;
    [[nodiscard]] Quaternion operator*( float32 scalar) const;
    [[nodiscard]] Quaternion operator/( float32 scalar) const;
    [[nodiscard]] Quaternion operator-() const;

    Quaternion& operator+=( Quaternion const& other );
    Quaternion& operator-=( Quaternion const& other );
    Quaternion& operator*=( Quaternion const& other );
    Quaternion& operator*=( float32 scalar );
    Quaternion& operator/=( float32 scalar );

    [[nodiscard]] explicit operator bool() const;
    [[nodiscard]] bool operator==( Quaternion const& other ) const;
    [[nodiscard]] bool operator!=( Quaternion const& other ) const;
};


#include "Quaternion.inl"

#endif