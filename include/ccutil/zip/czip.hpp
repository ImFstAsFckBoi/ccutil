#pragma once

#include <iterator>



namespace cc {

template <typename T1_iter, typename T2_iter>
class const_zip_iterator 
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::pair<const typename T1_iter::value_type, const typename T2_iter::value_type>;
    using reference = std::pair<typename std::reference_wrapper<typename T1_iter::value_type const>, typename std::reference_wrapper<typename T2_iter::value_type const>>;
    const_zip_iterator(T1_iter iter1, T2_iter iter2);

    reference operator*() const noexcept;

    bool operator==(const_zip_iterator const &other) const;
    bool operator!=(const_zip_iterator const &other) const;

    const_zip_iterator &operator++();
    const_zip_iterator operator++(int);

private:
    T1_iter __iter1;
    T2_iter __iter2;
};

template<typename T1, typename T2>
class const_zipper
{
public:
    using iterator = const_zip_iterator<typename T1::const_iterator, typename T2::const_iterator>;
    using const_iterator = iterator;
    const_zipper(T1 const &container1, T2 const &container2);
    ~const_zipper() = default;
    iterator begin() const;
    iterator end() const;

private:

    const T1 *__c1;
    const T2 *__c2;
};

template <typename T1, typename T2>
const_zipper<T1, T2> zip(T1 const &container1, T2 const &container2);

} // NAMESPACE CC

#include "czip.tpp"
