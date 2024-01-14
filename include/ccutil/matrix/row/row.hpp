#pragma once

#include "row_iter.hpp"

#include "ccutil/matrix.hpp"

#include <concepts>
#include <cstddef>


namespace cc
{
/**
 * @brief Subset of a matrix representing a row in the matrix.
 * 
 * @tparam T Element type. Any arithmetic type.
 * @tparam _columns Number of columns in the matrix.
 */
template <typename T, size_t _columns>
    requires std::is_arithmetic_v<T>
class row_subset
{
public:
    using iterator = row_iter<T, _columns>;
    using const_iterator = const_row_iter<T, _columns>;
    row_subset(T *base);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    /**
     * @brief Get reference of element in the row (bound checked).
     * 
     * @param index Index of the row (zero indexed)
     * @return T& Reference to the element at index.
     */
    T &at(size_t index);
    /**
     * @brief Get value of element in row. (Bound checked) 
     * 
     * @param index Index of the row
     * @return T Value of the element at index.
     */
    T at(size_t index) const;
    /**
     * @brief Get reference of element in the row (unchecked).
     * 
     * @param index Index of the row (zero indexed)
     * @return T& Reference to the element at index.
     */
    T &operator[](size_t index);
    /**
     * @brief Get value of element in row. (unchecked) 
     * 
     * @param index Index of the row
     * @return T Value of the element at index.
     */
    T operator[](size_t index) const;

private:
    T *__base;
};

} // NAMESPACE CC

#include "row.tpp"
