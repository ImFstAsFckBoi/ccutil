#pragma once

#include "column_iter.hpp"


#include <concepts>
#include <cstddef>

namespace cc
{
/**
 * @brief Subset of a matrix representing a column in the matrix.
 * 
 * @tparam T Element type. Any arithmetic type.
 * @tparam _rows Number of rows and columns in the matrix.
 * @tparam _columns Number of columns in the matrix.
 */
template <typename T, size_t _rows, size_t _columns >
    requires std::is_arithmetic_v<T>
class column_subset
{
public:
    using iterator = column_iter<T, _rows, _columns>;
    using const_iterator = const_column_iter<T, _rows, _columns>;

    /**
     * @brief !THIS CONSTRUCTOR SHOULD NOT BE USED. LET THE MATRIX CLASS CREATE THIS FOR YOU!
     */
    column_subset(T *base);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    /**
     * @brief Get reference of element in the column (bound checked).
     * 
     * @param index Index of the column (zero indexed)
     * @return T& Reference to the element at index.
     */
    T &at(size_t index);
    /**
     * @brief Get value of element in column. (Bound checked) 
     * 
     * @param index Index of the column
     * @return T Value of the element at index.
     */
    T at(size_t index) const;
    /**
     * @brief Get reference of element in the column (unchecked).
     * 
     * @param index Index of the column (zero indexed)
     * @return T& Reference to the element at index.
     */
    T &operator[](size_t index);
    /**
     * @brief Get value of element in column. (unchecked) 
     * 
     * @param index Index of the column
     * @return T Value of the element at index.
     */
    T operator[](size_t index) const;

private:
    T *__base;
};

} // NAMESPACE CC

#include "column.tpp"
