#ifndef MATH_MATRIX2X2_INL_INCLUDED
#define MATH_MATRIX2X2_INL_INCLUDED


template <uint8 otherColumns>
Matrix<2, otherColumns> Matrix2x2::operator*( Matrix<2, otherColumns> const& other ) const
{
    Matrix<2, otherColumns> result;
    for ( uint8 j = 0; j < otherColumns; ++j )
    {
        result.values[0][j] = _11 * other.values[0][j] + _12 * other.values[1][j];
        result.values[1][j] = _21 * other.values[0][j] + _22 * other.values[1][j];
    }
    return result;
}


template <uint8 otherRows, uint8 otherColumns>
bool Matrix2x2::operator==( Matrix<otherRows, otherColumns> const& ) const { return false; }

template <uint8 otherRows, uint8 otherColumns>
bool Matrix2x2::operator!=( Matrix<otherRows, otherColumns> const& ) const { return true; }


#endif