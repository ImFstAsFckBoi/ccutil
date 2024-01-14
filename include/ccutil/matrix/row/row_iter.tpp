#pragma once

#include "row_iter.hpp"

#include <cstddef>
#include <concepts>

namespace cc
{

template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns>::row_iter(T *data, size_t index)
    : __index{index}, __base{data}
{}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns> &
row_iter<T, _columns>::operator++()
{
    ++__index;
    return *this;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns> 
row_iter<T, _columns>::operator++(int)
{
    auto tmp = *this;
    ++__index;
    return tmp;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns> &
row_iter<T, _columns>::operator--()
{
    __index -= _columns;
    return *this;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns>
row_iter<T, _columns>::operator--(int)
{
    auto tmp = *this;
    __index -= _columns;
    return tmp;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns>
row_iter<T, _columns>::operator+(int offset)
{
    if (__index + offset > _columns)
        throw std::invalid_argument("Index out of range");
    return row_iter(__base, __index + offset);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns>
row_iter<T, _columns>::operator-(int offset)
{
    if (offset > __index)
        throw std::invalid_argument("Index out of range");
    return row_iter(__base, __index - offset);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_iter<T, _columns>::reference_type
row_iter<T, _columns>::operator*()
{
    return *(__base + __index);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
bool
row_iter<T, _columns>::operator==(row_iter const &other) const
{
    return __base + __index == other.__base + other.__index;
}

template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
bool
row_iter<T, _columns>::operator!=(row_iter const &other) const
{
    return __base + __index != other.__base + other.__index;
}


// CONST



template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns>::const_row_iter(T *data, size_t index)
    : __index{index}, __base{data}
{}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns> &
const_row_iter<T, _columns>::operator++()
{
    ++__index;
    return *this;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns> 
const_row_iter<T, _columns>::operator++(int)
{
    auto tmp = *this;
    ++__index;
    return tmp;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns> &
const_row_iter<T, _columns>::operator--()
{
    __index -= _columns;
    return *this;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns>
const_row_iter<T, _columns>::operator--(int)
{
    auto tmp = *this;
    __index -= _columns;
    return tmp;
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns>
const_row_iter<T, _columns>::operator+(int offset)
{
    if (__index + offset > _columns)
        throw std::invalid_argument("Index out of range");
    return const_row_iter(__base, __index + offset);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns>
const_row_iter<T, _columns>::operator-(int offset)
{
    if (offset > __index)
        throw std::invalid_argument("Index out of range");
    return const_row_iter(__base, __index - offset);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
const_row_iter<T, _columns>::reference_type
const_row_iter<T, _columns>::operator*() const
{
    return *(__base + __index);
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
bool
const_row_iter<T, _columns>::operator==(const_row_iter const &other) const
{
    return __base + __index == other.__base + other.__index;
}

template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
bool
const_row_iter<T, _columns>::operator!=(const_row_iter const &other) const
{
    return __base + __index != other.__base + other.__index;
}

} // NAMESPACE CC
