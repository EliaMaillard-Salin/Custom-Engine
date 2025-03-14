#ifndef MATH_MATRIX_HPP_INCLUDED
#define MATH_MATRIX_HPP_INCLUDED
#include "../define.h"



template <uint8 rows, uint8 columns>
struct Matrix
{
    float values[rows][columns] {};

    static Matrix const Null;

    Matrix() = default;
    Matrix( float const (&&table)[rows][columns] );
    Matrix( Matrix const& other );

    Matrix& operator=( Matrix const& other );

    [[nodiscard]] Matrix<columns, rows> Transpose() const;
    [[nodiscard]] Matrix<rows-1, columns-1> SubMatrix( uint8 row, uint8 column ) const;
    [[nodiscard]] Matrix SwapRow( uint8 first, uint8 second ) const;
    [[nodiscard]] Matrix SwapColumn( uint8 first, uint8 second ) const;

    Matrix& SelfSwapRow( uint8 first, uint8 second );
    Matrix& SelfSwapColumn( uint8 first, uint8 second );

    [[nodiscard]] bool IsNull() const;
    [[nodiscard]] bool IsIdentity() const;
    [[nodiscard]] bool IsSquare() const;
    [[nodiscard]] bool IsSymmetric() const;
    [[nodiscard]] bool IsOrthogonal() const;
    [[nodiscard]] bool IsDiagonal() const;
    [[nodiscard]] bool IsTriangular() const;
    [[nodiscard]] bool IsUpperTriangular() const;
    [[nodiscard]] bool IsLowerTriangular() const;

    template <uint8 otherColumns>
    [[nodiscard]] Matrix<rows, otherColumns> operator*( Matrix<columns, otherColumns> const& other ) const;
    [[nodiscard]] Matrix operator+( Matrix const& other ) const;
    [[nodiscard]] Matrix operator-( Matrix const& other ) const;
    [[nodiscard]] Matrix operator*( float scalar ) const;
    [[nodiscard]] Matrix operator/( float scalar ) const;

    Matrix& operator+=( Matrix const& other );
    Matrix& operator-=( Matrix const& other );
    Matrix& operator*=( float scalar );
    Matrix& operator/=( float scalar );

    [[nodiscard]] bool operator==( Matrix const& other ) const;
    [[nodiscard]] bool operator!=( Matrix const& other ) const;
    template <uint8 otherRows, uint8 otherColumns>
    [[nodiscard]] bool operator==( Matrix<otherRows, otherColumns> const& other ) const;
    template <uint8 otherRows, uint8 otherColumns>
    [[nodiscard]] bool operator!=( Matrix<otherRows, otherColumns> const& other ) const;
};



using Matrix1x1 = Matrix<1, 1>;
using Matrix2x2 = Matrix<2, 2>;
using Matrix3x3 = Matrix<3, 3>;
using Matrix4x4 = Matrix<4, 4>;

#include "Matrix.inl"

#include "SquareMatrix.hpp"
#include "Matrix1x1.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.hpp"

#endif