#pragma once

#include <concepts>
#include <cstddef>

namespace cc
{

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class column_iter
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using reference_type = value_type &;
    column_iter(T *data, size_t index = 0);
    column_iter &operator++();
    column_iter operator++(int);
    column_iter &operator--();
    column_iter operator--(int);
    column_iter operator+(int offset);
    column_iter operator-(int offset);

    reference_type operator*();

    bool operator==(column_iter const &other) const;
    bool operator!=(column_iter const &other) const;

private:
    size_t __index;
    value_type *__base;
};


template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class const_column_iter
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using reference_type = value_type &;
    const_column_iter(T *data, size_t index = 0);
    const_column_iter &operator++();
    const_column_iter operator++(int);
    const_column_iter &operator--();
    const_column_iter operator--(int);
    const_column_iter operator+(int offset);
    const_column_iter operator-(int offset);

    reference_type operator*() const;

    bool operator==(const_column_iter const &other) const;
    bool operator!=(const_column_iter const &other) const;

private:
    size_t __index;
    value_type *__base;
};

} // NAMESPACE CC

#include "column_iter.tpp"
