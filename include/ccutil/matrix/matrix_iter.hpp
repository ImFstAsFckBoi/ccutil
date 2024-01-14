#pragma once

#include <concepts>
#include <cstddef>
#include <iterator>

namespace cc
{

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class matrix_iter
{
public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using reference_type = value_type &;
        matrix_iter(T *data, size_t index = 0);

        matrix_iter &operator++();

        matrix_iter operator++(int);
        matrix_iter &operator--();
        matrix_iter operator--(int);

        matrix_iter operator+(int offset);
        matrix_iter operator-(int offset);

        reference_type operator*();

        bool operator==(matrix_iter const &other) const;
        bool operator!=(matrix_iter const &other) const;

    private:
        size_t __index;
        value_type *__base;
};

template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class const_matrix_iter
{
public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = const T;
        using reference_type = value_type &;
        const_matrix_iter(T const *data, size_t index = 0);

        const_matrix_iter &operator++();

        const_matrix_iter operator++(int);
        const_matrix_iter &operator--();
        const_matrix_iter operator--(int);

        const_matrix_iter operator+(int offset);
        const_matrix_iter operator-(int offset);

        reference_type operator*() const;

        bool operator==(const_matrix_iter const &other) const;
        bool operator!=(const_matrix_iter const &other) const;

    private:
        size_t __index;
        value_type *__base;
};
} // NAMESPACE CC

#include "matrix_iter.tpp"
