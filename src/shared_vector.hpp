#pragma once

#include <stdexcept>

namespace unstd
{

template <typename T>
class shared_vector;

template <typename T>
shared_vector<T> make_shared_vector(const shared_vector<T>& other, typename shared_vector<T>::const_iterator first, typename shared_vector<T>::const_iterator last);

template <typename T>
class shared_vector
{
public:
    shared_vector();
    ~shared_vector();

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

    void clear();
    void push_back(const value_type& value);
    void resize(size_type count);

    friend shared_vector<T> make_shared_vector<>(const shared_vector<T>& other, typename shared_vector<T>::const_iterator first, typename shared_vector<T>::const_iterator last);

private:
    // The local span
    size_type _offset = 0;
    size_type _length = 0;

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
shared_vector<T>::~shared_vector()
{
    if (_ref_count != nullptr && --(*_ref_count) == 0)
    {
        delete[] _data;
        delete _capacity;
        delete _size;
        delete _ref_count;
    }
}

template <typename T>
shared_vector<T>::shared_vector(const shared_vector& other) noexcept
    : _offset(other._offset), _length(other._length), _data(other._data), _capacity(other._capacity), _size(other._size), _ref_count(other._ref_count)
{
    (*_ref_count)++;
}

template <typename T>
const shared_vector<T>& shared_vector<T>::operator=(const shared_vector& other) noexcept
{
    if (this != &other)
    {
        _offset = other._offset;
        _length = other._length;
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
    : _offset(other._offset), _length(other._length), _data(other._data), _capacity(other._capacity), _size(other._size), _ref_count(other._ref_count)
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
        _offset = other._offset;
        _length = other._length;
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

template <typename T>
typename shared_vector<T>::reference shared_vector<T>::at(size_type pos)
{
    if (pos >= _length)
        throw std::out_of_range("shared_vector::at");

    return reinterpret_cast<pointer>(_data)[_offset + pos];

}

template <typename T>
typename shared_vector<T>::const_reference shared_vector<T>::at(size_type pos) const
{
    if (pos >= _length)
        throw std::out_of_range("shared_vector::at");

    return reinterpret_cast<const_pointer>(_data)[_offset + pos];
}

template <typename T>
typename shared_vector<T>::reference shared_vector<T>::operator[](size_type pos)
{
    return reinterpret_cast<pointer>(_data)[_offset + pos];
}

template <typename T>
typename shared_vector<T>::const_reference shared_vector<T>::operator[](size_type pos) const
{
    return reinterpret_cast<pointer>(_data)[_offset + pos];
}

template <typename T>
typename shared_vector<T>::reference shared_vector<T>::front()
{
    return reinterpret_cast<pointer>(_data)[_offset];
}

template <typename T>
typename shared_vector<T>::const_reference shared_vector<T>::front() const
{
    return reinterpret_cast<const_pointer>(_data)[_offset];
}

template <typename T>
typename shared_vector<T>::reference shared_vector<T>::back()
{
    return reinterpret_cast<pointer>(_data)[_offset + _length - 1];
}

template <typename T>
typename shared_vector<T>::const_reference shared_vector<T>::back() const
{
    return reinterpret_cast<pointer>(_data)[_offset + _length - 1];
}

template <typename T>
typename shared_vector<T>::pointer shared_vector<T>::data() noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset;
}

template <typename T>
typename shared_vector<T>::const_pointer shared_vector<T>::data() const noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset;
}

template <typename T>
typename shared_vector<T>::iterator shared_vector<T>::begin() noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset;
}

template <typename T>
typename shared_vector<T>::const_iterator shared_vector<T>::begin() const noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset;
}

template <typename T>
typename shared_vector<T>::iterator shared_vector<T>::end() noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset + _length;
}

template <typename T>
typename shared_vector<T>::const_iterator shared_vector<T>::end() const noexcept
{
    return reinterpret_cast<pointer>(_data) + _offset + _length;
}

template <typename T>
bool shared_vector<T>::empty() const noexcept
{
    return _length == 0;
}

template <typename T>
typename shared_vector<T>::size_type shared_vector<T>::size() const noexcept
{
    return _length;
}

template <typename T>
typename shared_vector<T>::size_type shared_vector<T>::max_size() const noexcept
{   
    return (_offset + _length == *_size) ? std::numeric_limits<size_type>::max() : _length;
}

template <typename T>
void shared_vector<T>::reserve(size_type new_cap)
{
    if (_offset + _length == *_size && _offset + new_cap > *_capacity)
    {
        void** new_data = new void*[_offset + new_cap];
        std::copy(_data, _data + *_size, new_data);
        delete[] _data;
        _data = new_data;

        *_capacity = _offset + new_cap;
    }
}

template <typename T>
typename shared_vector<T>::size_type shared_vector<T>::capacity() const noexcept
{
    return (_offset + _length == *_size) ? *_capacity - _offset : _length;
}

template <typename T>
void shared_vector<T>::shrink_to_fit()
{
    if (_offset + _length == *_size)
    {
        void** new_data = new void*[*_size];
        std::copy(_data, _data + *_size, new_data);
        delete[] _data;
        _data = new_data;

        *_capacity = *_size;
    }
}

template <typename T>
void shared_vector<T>::clear()
{
    if (_offset + _length == *_size)
    {
        _offset = 0;
        _length = 0;
    }
    else
    {
        throw std::domain_error("shared_vector::clear");
    }
}

template <typename T>
void shared_vector<T>::push_back(const_reference value)
{
    if (_offset + _length == *_size)
    {
        const size_type old_cap = capacity();
        if (old_cap < _length + 1)
            reserve(2*old_cap);

        reinterpret_cast<pointer>(_data)[_offset + _length] = value;
        _length++;
        *_size = _offset + _length;
    }
    else
    {
        throw std::domain_error("shared_vector::push_back");
    }
}

template <typename T>
void shared_vector<T>::resize(size_type count)
{
    if (_offset + _length == *_size)
    {
        if (capacity() < count)
            reserve(count);

        _length = count;
        *_size = _offset + _length;
    }
    else
    {
        throw std::domain_error("shared_vector::resize");
    }
}

template <typename T>
shared_vector<T> make_shared_vector(const shared_vector<T>& other, typename shared_vector<T>::const_iterator first, typename shared_vector<T>::const_iterator last)
{
    if (first < other.begin() or last > other.end())
        throw std::out_of_range("make_shared_vector");

    shared_vector<T> ret = other;
    ret._offset = std::distance(other.begin(), first);
    ret._length = std::distance(first, last);

    return ret;
}

}