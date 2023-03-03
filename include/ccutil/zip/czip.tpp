#pragma once
#include "czip.hpp"

namespace cc {



template<typename T1_iter, typename T2_iter>
const_zip_iterator<T1_iter, T2_iter>::const_zip_iterator(T1_iter iter1, T2_iter iter2)
    : __iter1  {iter1}, __iter2 {iter2}
{}

template<typename T1_iter, typename T2_iter>
typename const_zip_iterator<T1_iter, T2_iter>::reference const_zip_iterator<T1_iter, T2_iter>::operator*() const noexcept
{ return std::make_pair(std::cref(*__iter1), std::cref(*__iter2)); }


template<typename T1_iter, typename T2_iter>
bool const_zip_iterator<T1_iter, T2_iter>::operator==(const_zip_iterator const &other) const
{
    return (__iter1 == other.__iter1 || __iter2 == other.__iter2);
}

template<typename T1_iter, typename T2_iter>
const_zip_iterator<T1_iter, T2_iter> &const_zip_iterator<T1_iter, T2_iter>::operator++()
{
    ++__iter1;
    ++__iter2;
    return *this;
}


template<typename T1_iter, typename T2_iter>
const_zip_iterator<T1_iter, T2_iter> const_zip_iterator<T1_iter, T2_iter>::operator++(int)
{
    const_zip_iterator tmp = *this;
    ++*this;
    return tmp;
}

template<typename T1_iter, typename T2_iter>
bool const_zip_iterator<T1_iter, T2_iter>::operator!=(const_zip_iterator const &other) const
{ return !(*this == other); }

/*
 * ZIPPER
 */

template<typename T1, typename T2>
const_zipper<T1, T2>::const_zipper(T1 const &container1, T2 const &container2)
    : __c1{&container1}, __c2{&container2}
{}

template<typename T1, typename T2>
typename const_zipper<T1, T2>::iterator const_zipper<T1, T2>::begin() const
{ return const_zipper<T1, T2>::iterator(__c1->begin(), __c2->begin()); }

template<typename T1, typename T2>
typename const_zipper<T1, T2>::iterator const_zipper<T1, T2>::end() const
{ return const_zipper<T1, T2>::iterator(__c1->end(), __c2->end()); }

/**
 * @brief Create a new const_zipper object. 
 * 
 * @tparam T1 Iterable container type 1.
 * @tparam T2 Iterable container type 2.
 * @param container1 An iterable container.
 * @param container2 An iterable container.
 * @return const_zipper<T1, T2> Zipper object to get a const_zip_iterator from. 
 */
template <typename T1, typename T2>
const_zipper<T1, T2> zip(T1 const &container1, T2 const &container2)
{ return const_zipper<T1, T2>(container1, container2); }

} // NAMESPACE CC
