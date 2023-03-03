#pragma once

#include <iterator>

namespace cc {

template <typename T1_iter, typename T2_iter>
class zip_iterator 
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::pair<typename T1_iter::value_type, typename T2_iter::value_type>;
    using reference = std::pair<typename std::reference_wrapper<typename T1_iter::value_type>, typename std::reference_wrapper<typename T2_iter::value_type>>;
    zip_iterator(T1_iter iter1, T2_iter iter2);

    reference operator*() noexcept;

    bool operator==(zip_iterator const &other) const;
    bool operator!=(zip_iterator const &other) const;

    zip_iterator &operator++();
    zip_iterator operator++(int);

private:
    T1_iter __iter1;
    T2_iter __iter2;
};


template<typename T1, typename T2>
class zipper
{
private:
public:
    using iterator = zip_iterator<typename T1::iterator, typename T2::iterator>;
    
    zipper(T1 &container1, T2 &container2);
    ~zipper() = default;
    iterator begin();
    iterator end();

private:

    T1 *__c1;
    T2 *__c2;
};


template <typename T1, typename T2>
zipper<T1, T2> zip(T1 &container1, T2 &container2);

} // NAMESPACE CC

#include "zip.tpp"
