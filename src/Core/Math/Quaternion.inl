#ifndef MATH_QUATERNION_INL_INCLUDED
#define MATH_QUATERNION_INL_INCLUDED


inline Quaternion const Quaternion::Null {};
inline Quaternion const Quaternion::Identity { 0.0f, 0.0f, 0.0f, 1.0f };


inline bool Quaternion::IsNull() const { return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f; }
inline bool Quaternion::IsIdentity() const { return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f; }

inline Quaternion Quaternion::operator+( Quaternion const& other ) const { return Quaternion( x + other.x, y + other.y, z + other.z, w + other.w ); }
inline Quaternion Quaternion::operator-( Quaternion const& other ) const { return Quaternion( x - other.x, y - other.y, z - other.z, w - other.w ); }
inline Quaternion Quaternion::operator*( float32 const scalar ) const { return Quaternion( x * scalar, y * scalar, z * scalar, w * scalar ); }
inline Quaternion Quaternion::operator-() const { return Quaternion( -x, -y, -z, -w ); }

inline Quaternion::operator bool() const { return x != 0.0f || y != 0.0f || z != 0.0f || w != 0.0f; }
inline bool Quaternion::operator==( Quaternion const& other ) const { return this == &other || ( x == other.x && y == other.y && z == other.z && w == other.w ); }
inline bool Quaternion::operator!=( Quaternion const& other ) const { return this != &other && ( x != other.x || y != other.y || z != other.z || w != other.w ); }


#endif