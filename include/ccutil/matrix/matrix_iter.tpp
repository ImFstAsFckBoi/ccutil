#include "matrix_iter.hpp"

#include <concepts>
#include <cstddef>
#include <iterator>

namespace cc
{

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>::matrix_iter(T *data, size_t index)
    : __index{index}, __base{data}
{}

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns> &
matrix_iter<T, _rows, _columns>::operator++()
{
    ++__index;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>
matrix_iter<T, _rows, _columns>::operator++(int)
{
    auto tmp = *this;
    ++__index;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns> &
matrix_iter<T, _rows, _columns>::operator--()
{
    --__index;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>
matrix_iter<T, _rows, _columns>::operator--(int)
{
    auto tmp = *this;
    --__index;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>
matrix_iter<T, _rows, _columns>::operator+(int offset)
{
    if (__index + offset > _columns * _rows)
        throw std::invalid_argument("Index out of range");
    return matrix_iter(__base, __index + offset);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>
matrix_iter<T, _rows, _columns>::operator-(int offset)
{
    if (offset > __index)
        throw std::invalid_argument("Index out of range");
    return matrix_iter(__base, __index - offset);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
matrix_iter<T, _rows, _columns>::reference_type
matrix_iter<T, _rows, _columns>::operator*()
{ return *(__base + __index); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
matrix_iter<T, _rows, _columns>::operator==(matrix_iter<T, _rows, _columns> const &other) const
{ return __base + __index == other.__base + other.__index; }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
matrix_iter<T, _rows, _columns>::operator!=(matrix_iter<T, _rows, _columns> const &other) const
{ return __base + __index != other.__base + other.__index; }


// CONST


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>::const_matrix_iter(T const *data, size_t index)
    : __index{index}, __base{data}
{}

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns> &
const_matrix_iter<T, _rows, _columns>::operator++()
{
    ++__index;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>
const_matrix_iter<T, _rows, _columns>::operator++(int)
{
    auto tmp = *this;
    ++__index;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns> &
const_matrix_iter<T, _rows, _columns>::operator--()
{
    --__index;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>
const_matrix_iter<T, _rows, _columns>::operator--(int)
{
    auto tmp = *this;
    --__index;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>
const_matrix_iter<T, _rows, _columns>::operator+(int offset)
{
    if (__index + offset > _columns * _rows)
        throw std::invalid_argument("Index out of range");
    return const_matrix_iter(__base, __index + offset);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>
const_matrix_iter<T, _rows, _columns>::operator-(int offset)
{
    if (offset > __index)
        throw std::invalid_argument("Index out of range");
    return const_matrix_iter(__base, __index - offset);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_matrix_iter<T, _rows, _columns>::reference_type
const_matrix_iter<T, _rows, _columns>::operator*() const
{ return *(__base + __index); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
const_matrix_iter<T, _rows, _columns>::operator==(const_matrix_iter<T, _rows, _columns> const &other) const
{ return __base + __index == other.__base + other.__index; }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
const_matrix_iter<T, _rows, _columns>::operator!=(const_matrix_iter<T, _rows, _columns> const &other) const
{ return __base + __index != other.__base + other.__index; }

} // NAMESPACE CC
