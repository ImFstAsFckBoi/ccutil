#pragma once

#include "column_iter.hpp"

#include <concepts>
#include <cstddef>

namespace cc
{

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>::column_iter(T *data, size_t index)
    : __index{index}, __base{data}
{}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns> &
column_iter<T, _rows, _columns>::operator++()
{
    __index += _columns;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>
column_iter<T, _rows, _columns>::operator++(int)
{
    auto tmp = *this;
    __index += _columns;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns> &
column_iter<T, _rows, _columns>::operator--()
{
    __index -= _columns;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>
column_iter<T, _rows, _columns>::operator--(int)
{
    auto tmp = *this;
    __index -= _columns;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>
column_iter<T, _rows, _columns>::operator+(int offset)
{
    if (__index + offset * _columns > __base + _columns * _rows)
        throw std::invalid_argument("Index out of range");
    return column_iter(__base, __index + offset * _columns);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>
column_iter<T, _rows, _columns>::operator-(int offset)
{
    if (offset * _columns > __index)
        throw std::invalid_argument("Index out of range");
    return column_iter(__base, __index - offset * _columns);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_iter<T, _rows, _columns>::reference_type 
column_iter<T, _rows, _columns>::operator*()
{ return *(__base + __index); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
column_iter<T, _rows, _columns>::operator==(column_iter const &other) const
{ return __base + __index == other.__base + other.__index; }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
column_iter<T, _rows, _columns>::operator!=(column_iter const &other) const
{ return __base + __index != other.__base + other.__index; }


// CONST


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>::const_column_iter(T *data, size_t index)
    : __index{index}, __base{data}
{}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns> &
const_column_iter<T, _rows, _columns>::operator++()
{
    __index += _columns;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>
const_column_iter<T, _rows, _columns>::operator++(int)
{
    auto tmp = *this;
    __index += _columns;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns> &
const_column_iter<T, _rows, _columns>::operator--()
{
    __index -= _columns;
    return *this;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>
const_column_iter<T, _rows, _columns>::operator--(int)
{
    auto tmp = *this;
    __index -= _columns;
    return tmp;
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>
const_column_iter<T, _rows, _columns>::operator+(int offset)
{
    if (__index + offset * _columns > __base + _columns * _rows)
        throw std::invalid_argument("Index out of range");
    return const_column_iter(__base, __index + offset * _columns);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>
const_column_iter<T, _rows, _columns>::operator-(int offset)
{
    if (offset * _columns > __index)
        throw std::invalid_argument("Index out of range");
    return const_column_iter(__base, __index - offset * _columns);
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
const_column_iter<T, _rows, _columns>::reference_type 
const_column_iter<T, _rows, _columns>::operator*() const
{ return *(__base + __index); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
const_column_iter<T, _rows, _columns>::operator==(const_column_iter const &other) const
{ return __base + __index == other.__base + other.__index; }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
bool
const_column_iter<T, _rows, _columns>::operator!=(const_column_iter const &other) const
{ return __base + __index != other.__base + other.__index; }

} // NAMESPACE CC
