#pragma once

#include <cstddef>

namespace cc
{

template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
class row_iter
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using reference_type = value_type &;

    row_iter(T *data, size_t index = 0);

    row_iter &operator++();
    row_iter operator++(int);
    row_iter &operator--();
    row_iter operator--(int);

    row_iter operator+(int offset);
    row_iter operator-(int offset);

    reference_type operator*();
    bool operator==(row_iter const &other) const;
    bool operator!=(row_iter const &other) const;

private:
    size_t __index;
    value_type *__base;
};


template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
class const_row_iter
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = const T;
    using reference_type = value_type &;

    const_row_iter(T *data, size_t index = 0);

    const_row_iter &operator++();
    const_row_iter operator++(int);
    const_row_iter &operator--();
    const_row_iter operator--(int);

    const_row_iter operator+(int offset);
    const_row_iter operator-(int offset);

    reference_type operator*() const;
    bool operator==(const_row_iter const &other) const;
    bool operator!=(const_row_iter const &other) const;

private:
    size_t __index;
    value_type *__base;
};

} // NAMESPACE CC

#include "row_iter.tpp"
