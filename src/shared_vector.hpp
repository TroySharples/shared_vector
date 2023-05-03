#pragma once

#include <vector>

namespace unstd
{

template <typename T>
class shared_vector
{
public:
    shared_vector();

    shared_vector(const shared_vector& other) noexcept;
    const shared_vector& operator=(const shared_vector& other) noexcept;

    shared_vector(shared_vector&& other) noexcept;
    shared_vector& operator=(shared_vector&& other) noexcept;

    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data() noexcept;
    const_pointer data() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    void clear() noexcept;
    void push_back(const value_type& value);
    void resize(size_type count);

private:
    // The local span
    size_type offset = 0;
    size_type length = 0;

    // The shared vector
    void** _data;
    size_type* _capacity;
    size_type* _size;
    size_type* _ref_count;
};

template <typename T>
shared_vector<T>::shared_vector()
{
    constexpr size_type initial_capacity = 4;
    _data = new void*[initial_capacity];
    _capacity = new size_type(initial_capacity);
    *_capacity = initial_capacity;

    _size = new size_type(0);

    _ref_count = new size_type(1);
}

template <typename T>
shared_vector<T>::shared_vector(const shared_vector& other) noexcept
    : _data(other._data), _capacity(other._capacity), _size(other._size), _ref_count(other._ref_count)
{
    (*_ref_count)++;
}

template <typename T>
const shared_vector<T>& shared_vector<T>::operator=(const shared_vector& other) noexcept
{
    if (this != &other)
    {
        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;
        _ref_count = other._ref_count;
        (*_ref_count)++;
    }

    return *this;
}

template <typename T>
shared_vector<T>::shared_vector(shared_vector&& other) noexcept
    : _data(other._data), _capacity(other._capacity), _size(other._size), _ref_count(other._ref_count)
{
    other._data = nullptr;
    other._capacity = nullptr;
    other._size = nullptr;
    other._ref_count = nullptr;
}

template <typename T>
shared_vector<T>& shared_vector<T>::operator=(shared_vector&& other) noexcept
{
    if (this != &other)
    {
        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;
        _ref_count = other._ref_count;

        other._data = nullptr;
        other._capacity = nullptr;
        other._size = nullptr;
        other._ref_count = nullptr;
    }

    return *this;
}

}