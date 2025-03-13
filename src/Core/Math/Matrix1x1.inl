#ifndef MATH_MATRIX1X1_INL_INCLUDED
#define MATH_MATRIX1X1_INL_INCLUDED


template <uint8 otherColumns>
Matrix<1, otherColumns> Matrix1x1::operator*( Matrix<1, otherColumns> const& other ) const
{
    Matrix<1, otherColumns> result;
    for ( uint8 j = 0; j < otherColumns; ++j )
        result.values[0][j] = _11 * other.values[0][j];
    return result;
}


template <uint8 otherRows, uint8 otherColumns>
bool Matrix1x1::operator==( Matrix<otherRows, otherColumns> const& ) const { return false; }

template <uint8 otherRows, uint8 otherColumns>
bool Matrix1x1::operator!=( Matrix<otherRows, otherColumns> const& ) const { return true; }


#endif