#ifndef HASHMAPITERATOR_HPP
#define HASHMAPITERATOR_HPP


#include "./HashMapIterator.h"
#include "HashMapIterator.h"


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>::HashMapIterator():
    _bucket_array_ptr{nullptr},
    _bucket_index{0},
    _curr_node{nullptr}
{
    ;
}


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>::HashMapIterator(
    bucket_array_type* bucket_array_ptr,
    size_type bucket_index,
    node_ptr node
):
    _bucket_array_ptr{bucket_array_ptr},
    _bucket_index{bucket_index},
    _curr_node{node}
{
    ;
}


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>::operator HashMapIterator<Map, true>() const noexcept {
    return HashMapIterator<Map, true>{_bucket_array_ptr, _bucket_index, _curr_node};
}


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>::reference HashMapIterator<Map, IsConst>::operator*() const {
    return _curr_node->value;
}


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>::pointer HashMapIterator<Map, IsConst>::operator->() const
{
    return &(_curr_node->value);
}

template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst>& HashMapIterator<Map, IsConst>::operator++() {
    _curr_node = _curr_node->next;
    if (_curr_node == nullptr) {
        // ++_bucket_index;
        for (++_bucket_index;  _bucket_index < _bucket_array_ptr->size() && (*_bucket_array_ptr)[_bucket_index] == nullptr; ++_bucket_index)
            ;
        if (_bucket_index < _bucket_array_ptr->size()) {
            _curr_node = (*_bucket_array_ptr)[_bucket_index];
        } else {
            _curr_node = nullptr;
        }
    }
    return *this;
}


template<typename Map, bool IsConst>
HashMapIterator<Map, IsConst> HashMapIterator<Map, IsConst>::operator++(int) {
    auto copy = *this;
    this->operator++();
    return copy;
}


template<typename _Map>
bool operator==(const HashMapIterator<_Map, true>& lhs, const HashMapIterator<_Map, true>& rhs) {
    return lhs._curr_node == rhs._curr_node;
}


template<typename Map, bool IsConst>
bool operator!=(const HashMapIterator<Map, IsConst>& lhs, const HashMapIterator<Map, IsConst>& rhs) {
    return !(lhs == rhs);
}


#endif // HASHMAPITERATOR_HPP