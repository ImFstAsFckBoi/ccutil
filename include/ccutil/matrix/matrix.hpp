#pragma once

#include "matrix_iter.hpp"
#include "row/row.hpp"
#include "column/column.hpp"
#include "ccutil/str.hpp"

#include <ostream>
#include <cstring>
#include <concepts>
#include <iomanip>
#include <cassert>


namespace cc
{

// Forward declaration
template<typename T>
    requires std::is_arithmetic_v<T>
class vector2;

template<typename T>
    requires std::is_arithmetic_v<T>
class vector3;

/**
 * @brief Mathematical matrix with elements any artihmietic type T.
 * 
 * @tparam T Any arithmetic type. e.g. int, float, etc.
 * @tparam _rows Number of rows.
 * @tparam _columns Number of columns.
 */
template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class matrix
{
private:
    using row_t = row_subset<T, _columns>;
    using const_row_t = row_subset<const T, _columns>;
    using column_t = column_subset<T, _rows, _columns>;
    using const_column_t = column_subset<const T, _rows, _columns>;
public:
    using iterator = matrix_iter<T, _rows, _columns>;
    using const_iterator = const_matrix_iter<T, _rows, _columns>;

    /**
     * @brief Construct a new matrix with all zeros.
     * 
     */
    matrix();
    /**
     * @brief Construct a new matrix from a data buffer.
     * 
     * @param data type T data buffer.
     * @param n Number of elements to take, NOT BYTES!.
     * Defaults to the amount the matrix can fit.
     */
    matrix(T const *data, size_t n = _rows * _columns);
    /**
     * @brief Destroy the matrix object.
     * 
     */
    virtual ~matrix() = default;
    /**
     * @brief Get reference to element at any position in the matrix.
     * 
     * @param row Row to select from.
     * @param column Column to select from.
     * @return T& Reference to object at position.
     */
    T &at(size_t row, size_t column);
    /**
     * @brief Get element at any position in the matrix (bound checked).
     * 
     * @param row Row to select from (zero indexed).
     * @param column Column to select from (zero indexed).
     * @return T Value at position.
     */
    T at(size_t row, size_t column) const;
    /**
     * @brief Access a row of the matrix.
     * 
     * @param row Index of row to access.
     * @return row_t Row object.
     */
    row_t row(size_t row);
    /**
     * @brief Access a column of the matrix.
     * 
     * @param column Index of column to access.
     * @return column_t Column object.
     */
    column_t column(size_t column);
    /**
     * @brief Access a const row of the matrix.
     * 
     * @param row Index of row to access.
     * @return const const_row_t Const row object.
     */
    const const_row_t row(size_t row) const;
    /**
     * @brief Access a const column of the matrix.
     * 
     * @param column Index of column to access.
     * @return const const_column_t Cost column object.
     */
    const const_column_t column(size_t column) const;
    /**
     * @brief Starting iterator for entire matrix.
     * 
     * @return iterator Iterator object at beginning.
     */
    iterator begin();
    /**
     * @brief End iterator for entire matrix.
     * 
     * @return iterator Iterator object at end.
     */
    iterator end();
    /**
     * @brief Starting const iterator for entire matrix.
     * 
     * @return const_iterator Const iterator object at beginning.
     */
    const_iterator begin() const;
    /**
     * @brief End const iterator for entire matrix.
     * 
     * @return const_iterator Const iterator object at end.
     */
    const_iterator end() const;
    /**
     * @brief Access row via subscript. Not bound checked.
     * 
     * @param row Index of row to access.
     * @return row_t Row object.
     */
    inline row_t operator[](size_t row);
    /**
     * @brief Access column via subscript. Not bound checked.
     * 
     * @param row Index of column to access.
     * @return const_row_t Column object.
     */
    inline const_row_t operator[](size_t row) const;

#if _cplusplus >= 2023
    T &operator[](size_t row, size_t column);
    T operator[](size_t row, size_t column) const;
#endif
    /**
     * @brief Get reference to largest element in the matrix.
     * 
     * @return T& Reference to largest element.
     */
    T &maxv();
    /**
     * @brief Get value of largest element in the matrix.
     * 
     * @return T Value of largest element.
     */
    T maxv() const;
    /**
     * @brief Get position of largest element in the matrix.
     * 
     * @return std::pair<size_t, size_t> Pair of row and column position in the matrix.
     */
    std::pair<size_t, size_t> maxl() const;
    /**
     * @brief Element-wise addition with a scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Value to add.
     * @return matrix<T, _rows, _columns> Resulting matrix.
     */
    template<typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix operator+(T_scalar scalar) const;
    /**
     * @brief Element-wise addition and assignment with a scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Value to add.
     * @return matrix<T, _rows, _columns>& Reference to matrix.
     */
    template<typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix &operator+=(T_scalar scalar);
    /**
     * @brief Element-wise subtraction with a scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Value to subtract.
     * @return matrix<T, _rows, _columns> Resulting matrix.
     */
    template<typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix operator-(T_scalar scalar) const;
    /**
     * @brief Element-wise subtraction and assignment with a scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Value to subtract.
     * @return matrix<T, _rows, _columns>& Reference to matrix.
     */
    template<typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix &operator-=(T_scalar scalar);
    /**
     * @brief Matrix addition.
     * 
     * @param other Other matrix to add.
     * @return matrix<T, _rows, _columns> Resulting Matrix
     */
    matrix operator+(matrix &other) const;
    /**
     * @brief Matrix addition and assignment.
     * 
     * @param other Other matrix to add.
     * @return matrix<T, _rows, _columns>& Reference to matrix.
     */
    matrix &operator+=(matrix &other);
    /**
     * @brief Matrix subtraction.
     * 
     * @param other Other matrix to add.
     * @return matrix<T, _rows, _columns> Resulting matrix.
     */
    matrix operator-(matrix &other) const;
    /**
     * @brief Matrix subtraction and assignment.
     * 
     * @param other Other matrix to add.
     * @return matrix<T, _rows, _columns>& Reference to matrix.
     */
    matrix &operator-=(matrix &other);
    /**
     * @brief Element-wise multiplication with scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Scalar to multiply by.
     * @return matrix<T, _rows, _columns> Resulting matrix.
     */
    template<typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix<T, _rows, _columns> operator*(T_scalar scalar) const;
    /**
     * @brief Element-wise multiplication and assignment with scalar.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Scalar to multiply by.
     * @return matrix<T, _rows, _columns>& Reference to matrix
     */
    template <typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix<T, _rows, _columns> &operator*=(T_scalar scalar);
    /**
     * @brief Matrix multiplication.
     * 
     * @tparam __rows Row of other matrix
     * @tparam __columns Columns of other matrix.
     * @param other Other matrix to multiply by.
     * @return matrix<T, _rows, __columns>& Resulting matrix.
     */
    template <size_t __rows, size_t __columns>
        requires(_columns == __rows)
    matrix<T, _rows, __columns> operator*(matrix<T, __rows, __columns> const &other) const;
    /**
     * @brief Element-wise exponent.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Scalar to raise to the power of.
     * @return matrix<T, _rows, _columns> Resulting matrix.
     */
    template <typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix pow(T_scalar scalar) const;
    /**
     * @brief Element-wise exponent to existing matrix.
     * 
     * @tparam T_scalar Any arithmetic type.
     * @param scalar Scalar to raise to the power of.
     * @return matrix<T, _rows, _columns>& Reference to existing matrix.
     */
    template <typename T_scalar>
        requires std::is_arithmetic_v<T_scalar>
    matrix &self_pow(T_scalar scalar);
    /**
     * @brief The tranpose of the matrix.
     * 
     * @return matrix<T, _columns, _rows> Resulting matrix.
     */
    matrix<T, _columns, _rows> transpose() const;
    /**
     * @brief Print the matrix to and ostream.
     * 
     * @param os std::ostream object.
     * @param mat Matrix to print.
     * @return ostream& Reference to ostream object
     */
    template <typename _T, size_t __rows, size_t __columns>
        requires std::is_arithmetic_v<_T>
    friend std::ostream &operator<<(std::ostream &os, matrix<_T, __rows, __columns> const &mat);
    /**
     * @brief Get pointer to data container.
     * 
     * @return T* Pointer.
     */
    inline T *data();
    /**
     * @brief Get const pointer to data container.
     * 
     * @return T const* const pointer
     */
    inline T const *data() const;
    /**
     * @brief Get number to rows in the matrix.
     * 
     * @return size_t Number of rows.
     */
    inline size_t rows() const noexcept;
    /**
     * @brief Get number of columns in the matrix.
     * 
     * @return size_t Number of columns.
     */
    inline size_t columns() const noexcept;
    
    // Following methods have a phantom template parameter
    // I dont know of a better way of using requirements
    // for conditional compilation without non-empty templates.

    /**
     * @brief Get the identity (or eye) of the matrix.
     * Only valid for square matrices.
     */
    template <int phantom = 1>
        requires(_rows == _columns)
    static matrix identity();


    // Implicit type conversion to vectors if 
    // Dimensions are valid.

    template <int phantom = 1>
        requires (_rows == 2, _columns == 1)
    operator vector2<T> () const
    { return vector2<T>(this->__data); }


    template <int phantom = 1>
        requires (_rows == 3, _columns == 1)
    operator vector3<T> () const
    { return vector3<T>(this->__data); }
    
protected:
    T __data[_columns * _rows];
};


/**
 * @brief 2D vector front end for the matrix class.
 * 
 * @tparam T 
 */
template<typename T>
    requires std::is_arithmetic_v<T>
class vector2 : public cc::matrix<T, 2, 1>
{
public:
    vector2()
        :  cc::matrix<T, 2, 1>(), x{*(this->__data)}, y{*(this->__data + 1)}
    {}

    vector2(T const *data)
        :  cc::matrix<T, 2, 1>(data), x{*(this->__data)}, y{*(this->__data + 1)}
    {}

    vector2(T x, T y)
        : vector2<T>()
    { this->x = x; this->y = y; }

    T &x;
    T &y;
};

/**
 * @brief 3D vector front end for the matrix class.
 * 
 * @tparam T 
 */
template<typename T>
    requires std::is_arithmetic_v<T>
class vector3 : public cc::matrix<T, 3, 1>
{
public:
    vector3()
        :  cc::matrix<T, 3, 1>(), x{*(this->__data)}, y{*(this->__data + 1)}, z{*(this->__data + 2)}
    {}
    
    vector3(T const *data)
        :  cc::matrix<T, 3, 1>(data), x{*(this->__data)}, y{*(this->__data + 1)}, z{*(this->__data + 2)}
    {}

    vector3(T x, T y, T z)
        : vector3<T>()
    { this->x = x; this->y = y; this->z = z; }

    T &x;
    T &y;
    T &z;
};


template <size_t rows, size_t columns>
using matrixf = matrix<float, rows, columns>;
template <size_t rows, size_t columns>
using matrixd = matrix<double, rows, columns>;

template <size_t rows, size_t columns>
using matrixi = matrix<int32_t, rows, columns>;

template <size_t rows, size_t columns>
using matrixi8 = matrix<int8_t, rows, columns>;

template <size_t rows, size_t columns>
using matrixi16 = matrix<int16_t, rows, columns>;

template <size_t rows, size_t columns>
using matrixi32 = matrix<int32_t, rows, columns>;

template <size_t rows, size_t columns>
using matrixi64 = matrix<int64_t, rows, columns>;

} // NAMESPACE CC

#include "matrix.tpp"
