#ifndef MATH_MATRIX3X3_INL_INCLUDED
#define MATH_MATRIX3X3_INL_INCLUDED


template <uint8 otherColumns>
Matrix<3, otherColumns> Matrix3x3::operator*( Matrix<3, otherColumns> const& other ) const
{
    Matrix<3, otherColumns> result;
    for ( uint8 j = 0; j < otherColumns; ++j )
    {
        result.values[0][j] = _11 * other.values[0][j] + _12 * other.values[1][j] + _13 * other.values[2][j];
        result.values[1][j] = _21 * other.values[0][j] + _22 * other.values[1][j] + _23 * other.values[2][j];
        result.values[2][j] = _31 * other.values[0][j] + _32 * other.values[1][j] + _33 * other.values[2][j];
    }
    return result;
}


template <uint8 otherRows, uint8 otherColumns>
bool Matrix3x3::operator==( Matrix<otherRows, otherColumns> const& ) const { return false; }

template <uint8 otherRows, uint8 otherColumns>
bool Matrix3x3::operator!=( Matrix<otherRows, otherColumns> const& ) const { return true; }


#endif