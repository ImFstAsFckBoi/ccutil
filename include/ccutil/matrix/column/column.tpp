#pragma once

#include "column.hpp"

#include <cstddef>
#include <concepts>

namespace cc
{

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_subset<T, _rows, _columns>::column_subset(T *base)
    : __base{base}
{}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_subset<T, _rows, _columns>::iterator
column_subset<T, _rows, _columns>::begin()
{ return iterator(__base); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_subset<T, _rows, _columns>::iterator
column_subset<T, _rows, _columns>::end()
{ return iterator(__base, _rows * _columns); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_subset<T, _rows, _columns>::const_iterator
column_subset<T, _rows, _columns>::begin() const
{ return const_iterator(__base); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
column_subset<T, _rows, _columns>::const_iterator
column_subset<T, _rows, _columns>::end() const
{ return const_iterator(__base, _rows * _columns); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
T &
column_subset<T, _rows, _columns>::at(size_t index)
{
    if (index >= _rows)
        throw std::invalid_argument("Index out of range.");

    return *this[index];
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
T
column_subset<T, _rows, _columns>::at(size_t index) const
{
    if (index >= _rows)
        throw std::invalid_argument("Index out of range.");

    return *this[index];
}


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
T &
column_subset<T, _rows, _columns>::operator[](size_t index)
{ return *(__base + index * _columns); }


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
T
column_subset<T, _rows, _columns>::operator[](size_t index) const
{ return *(__base + index * _columns); }

} // NAMESPACE CC
