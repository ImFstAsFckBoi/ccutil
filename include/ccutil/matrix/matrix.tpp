#pragma once

#include "matrix.hpp"
#include "ccutil/zip.hpp"
#include <cstring>
#include <cmath>
namespace cc
{


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::matrix()
    : __data{}
{}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::matrix(T const *data, size_t n)
    : __data{}
{
    std::memcpy(__data, data, n * sizeof(T));
}

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T &
matrix<T, _rows, _columns>::at(size_t row, size_t column)
{
    T *addr = __data + row * _columns + column;
    if (addr >= __data + _columns * _rows)
        throw std::invalid_argument("Index out of range");

    return *(addr);
}

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T
matrix<T, _rows, _columns>::at(size_t row, size_t column) const
{
    T const *addr = __data + row * _columns + column;
    if (addr >= __data + _columns * _rows)
        throw std::invalid_argument("Index out of range");

    return *(addr);
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::row_t
matrix<T, _rows, _columns>::row(size_t row)
{
    if (row >= _rows)
        throw std::invalid_argument("Index out of range");
    return row_t(__data + row * _columns);
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::column_t
matrix<T, _rows, _columns>::column(size_t column)
{
        if (column >= _columns)
        throw std::invalid_argument("Index out of range");
    return column_t(__data + column);
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
const matrix<T, _rows, _columns>::const_row_t
matrix<T, _rows, _columns>::row(size_t row) const
{
    if (row >= _rows)
        throw std::invalid_argument("Index out of range");
    return const_row_t(__data + row * _columns);
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
const matrix<T, _rows, _columns>::const_column_t
matrix<T, _rows, _columns>::column(size_t column) const
{
    if (column >= _columns)
        throw std::invalid_argument("Index out of range");
    return const_column_t(__data + column);
}

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::iterator
matrix<T, _rows, _columns>::begin()
{ return iterator(__data); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::iterator
matrix<T, _rows, _columns>::end()
{ return iterator(__data, _columns * _rows); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::const_iterator
matrix<T, _rows, _columns>::begin() const
{ return const_iterator(__data); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::const_iterator
matrix<T, _rows, _columns>::end() const
{ return const_iterator(__data, _columns * _rows); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::row_t
matrix<T, _rows, _columns>::operator[](size_t row)
{ return row_t(__data + row * _columns); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>::const_row_t
matrix<T, _rows, _columns>::operator[](size_t row) const
{ return const_row_t(__data + row * _columns); }


#if _cplusplus >= 2023
template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T &
matrix<T, _rows, _columns>::operator[](size_t row, size_t column)
{ return *(__data + row * _columns + column); }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T
matrix<T, _rows, _columns>::operator[](size_t row, size_t column) const
{ return *(__data + row * _columns + column); }
#endif

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
inline size_t
matrix<T, _rows, _columns>::columns() const noexcept
{ return _columns; }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
inline size_t
matrix<T, _rows, _columns>::rows() const noexcept
{ return _rows; }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T &
matrix<T, _rows, _columns>::maxv()
{
    T *max = __data;
    for(auto &i: *this)
        max = i > *max ? &i : max;

    return *max;

}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T
matrix<T, _rows, _columns>::maxv() const
{
    T max = 0;
    for(auto i: *this)
        max = i > max ? i : max;

    return max;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
std::pair<size_t, size_t>
matrix<T, _rows, _columns>::maxl() const
{
    T max{0};
    std::pair<size_t, size_t> l;
    for (int h{0}; h < _rows; ++h)
    {
        for (int w{0}; w < _columns; ++w)
        {
            if (at(h, w) > max)
            {
                max = at(h, w);
                l = std::make_pair(h, w);
            }
        }
    }
    return l;
}


template<typename T, size_t _rows, size_t _columns>
    requires (std::is_arithmetic_v<T>)
template<typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::operator+=(T_scalar scalar)
{
    for (T &el : *this)
        el += scalar;

    return *this;
}


template<typename T, size_t _rows, size_t _columns>
    requires (std::is_arithmetic_v<T>)
template<typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::operator-=(T_scalar scalar)
{
    for (T &el : *this)
        el -= scalar;

    return *this;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::operator+=(matrix &other)
{
    for (auto p : cc::zip(*this, other))
        p.first.get() += p.second.get();
    return *this;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::operator-=(matrix &other)
{
    for (auto p : cc::zip(*this, other))
        p.first.get() -= p.second.get();
    return *this;
}

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template<typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns>  matrix<T, _rows, _columns>::operator+(T_scalar scalar) const
{
    matrix<T, _rows, _columns> m(*this);
    for (auto &i : m)
        i += scalar;
    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template<typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns>  matrix<T, _rows, _columns>::operator-(T_scalar scalar) const
{
    matrix<T, _rows, _columns> m(*this);
    for (auto &i : m)
        i -= scalar;
    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>  matrix<T, _rows, _columns>::operator+(matrix &other) const
{
    matrix<T, _rows, _columns> m(*this);
    for (auto p : cc::zip(m, other))
        p.first.get() += p.second.get();
    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
matrix<T, _rows, _columns>  matrix<T, _rows, _columns>::operator-(matrix &other) const
{
    matrix<T, _rows, _columns> m(*this);
    for (auto p : cc::zip(m, other))
        p.first.get() -= p.second.get();
    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template <size_t __rows, size_t __columns>
    requires (_columns == __rows)
matrix<T, _rows, __columns>
matrix<T, _rows, _columns>::operator*(matrix<T, __rows, __columns> const &other) const
{
    matrix<T, _rows, __columns> m;
    
    for (int cs{0}; cs < __columns; ++cs)
    for (int rf{0}; rf < _rows; ++rf)
    for (int cf_rs{0}; cf_rs < _columns; ++cf_rs)
        m.at(rf, cs) += this->at(rf, cf_rs) * other.at(cf_rs, cs);

    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template<typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns>
matrix<T, _rows, _columns>::operator*(T_scalar scalar) const
{
    matrix<T, _rows, _columns> m{*this};

      for (auto &i : m)
        i *= scalar;

      return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template <typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::operator*=(T_scalar scalar)
{
    for (auto &i : *this)
        i *= scalar;

    return *this;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template <typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns>
matrix<T, _rows, _columns>::pow(T_scalar scalar) const
{
    auto m{*this};

    for (auto &i : m)
        i = std::pow(i, scalar);

    return m;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template <typename T_scalar>
    requires std::is_arithmetic_v<T_scalar>
matrix<T, _rows, _columns> &
matrix<T, _rows, _columns>::self_pow(T_scalar scalar)
{
    for (auto &i : *this)
        i = std::pow(i, scalar);

    return *this;
}

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>

matrix<T, _columns, _rows>
matrix<T, _rows, _columns>::transpose() const
{
    matrix<T, _columns, _rows> m;

    for (int h{0}; h < _rows; ++h)
    for (int w{0}; w < _columns;  ++w)
        m.at(w, h) = at(h, w);

    return m;
}


template<typename _T, size_t __rows, size_t __columns>
    requires std::is_arithmetic_v<_T>
std::ostream &
operator<<(std::ostream &os, matrix<_T, __rows, __columns> const &mat)
{
    int digs = cc::digits(static_cast<int>(mat.maxv()));
    for (int i{0}; i < __rows; ++i)
    {
        for (_T j : mat[i])
            os << std::setw(digs) << std::setfill(' ') << std::right << j << ' ';
        os << std::endl;
    }

    return os;
}


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T *
matrix<T, _rows, _columns>::data()
{ return __data; }


template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
T const *
matrix<T, _rows, _columns>::data() const
{ return __data; }

template<typename T, size_t _rows, size_t _columns>
    requires std::is_arithmetic_v<T>
template<int phantom>
    requires (_rows == _columns)
matrix<T, _rows, _columns>
matrix<T, _rows, _columns>::identity()
{
    matrix m{};
    for (int i{0}; i < _rows; ++i)
        m.at(i, i) = 1; 

    return m;
}

} // NAMESPACE cc
