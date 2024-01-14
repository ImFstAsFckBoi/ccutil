#pragma once

#include "row.hpp"

#include <cstddef>
#include <concepts>

namespace cc
{

template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_subset<T, _columns>::row_subset(T *base)
    : __base{base}
{}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_subset<T, _columns>::iterator
row_subset<T, _columns>::begin()
{ return iterator(__base); }


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_subset<T, _columns>::iterator
row_subset<T, _columns>::end()
{ return iterator(__base, _columns); }


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_subset<T, _columns>::const_iterator
row_subset<T, _columns>::begin() const
{ return const_iterator(__base); }


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
row_subset<T, _columns>::const_iterator
row_subset<T, _columns>::end() const
{ return const_iterator(__base, _columns); }


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
T &
row_subset<T, _columns>::at(size_t index)
{
    if (index >= _columns)
        throw std::invalid_argument("Index out of range");
    return *this[index];
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
T
row_subset<T, _columns>::at(size_t index) const
{
    if (index >= _columns)
        throw std::invalid_argument("Index out of range");
    return *this[index];
}


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
T &
row_subset<T, _columns>::operator[](size_t index)
{ return *(__base + index); }


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
T
row_subset<T, _columns>::operator[](size_t index) const
{ return *(__base + index); }

} // NAMESPACE CC
