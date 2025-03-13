#include "Quaternion.h"

#include "Vector3.hpp"

#include <cmath>


Quaternion::Quaternion( float32 const x, float32 const y, float32 const z, float32 const w ):
    x( x ),
    y( y ),
    z( z ),
    w( w ) {}


Quaternion& Quaternion::operator=( Quaternion const& other )
{
    if ( this == &other ) return *this;
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}


void Quaternion::FromAxisAngle( Vector3f const& axis, float32 angle )
{
    angle *= 0.5f;
    float32 const angleSin = sin( angle );
    x = axis.x * angleSin;
    y = axis.y * angleSin;
    z = axis.z * angleSin;
    w = cos( angle );
}


Quaternion Quaternion::operator*( Quaternion const& other ) const
{
    return Quaternion(
        w * other.x + other.w * x + y * other.z - z * other.y,
        w * other.y + other.w * y + z * other.x - x * other.z,
        w * other.z + other.w * z + x * other.y - y * other.x,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion Quaternion::operator/( float32 const scalar ) const
{
    assert( ( scalar != 0.0f ) );
    float32 const invScalar = 1.0f / scalar;
    return Quaternion( x * invScalar, y * invScalar, z * invScalar, w * invScalar );
}


Quaternion& Quaternion::operator+=( Quaternion const& other )
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Quaternion& Quaternion::operator-=( Quaternion const& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Quaternion& Quaternion::operator*=( Quaternion const& other )
{
    Quaternion const copy( *this );
    x = copy.w * other.x + other.w * copy.x + copy.y * other.z - copy.z * other.y;
    y = copy.w * other.y + other.w * copy.y + copy.z * other.x - copy.x * other.z;
    z = copy.w * other.z + other.w * copy.z + copy.x * other.y - copy.y * other.x;
    w = copy.w * other.w - copy.x * other.x - copy.y * other.y - copy.z * other.z;
    return *this;
}

Quaternion& Quaternion::operator*=( float32 const scalar )
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Quaternion& Quaternion::operator/=( float32 const scalar )
{
    assert( ( scalar != 0.0f ) );
    float32 const invScalar = 1.0f / scalar;
    x *= invScalar;
    y *= invScalar;
    z *= invScalar;
    w *= invScalar;
    return *this;
}