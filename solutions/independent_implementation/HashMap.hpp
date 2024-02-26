#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "./HashMap.h"
#include <iostream>
#include <cassert>


template<typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(size_type nbuckets, const H& hasher):
    _buckets{nbuckets, nullptr},
    _hash_function{hasher},
    _node_size{0}
{
    ;
}


template<typename K, typename M, typename H>
template<typename InputIt>
HashMap<K, M, H>::HashMap(
    InputIt first, 
    InputIt last, 
    size_type nbuckets, 
    const H& hasher
):
    HashMap{nbuckets, hasher}
{
    for (auto& it = first; it != last; ++it) {
        insert(*it);
    }
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::~HashMap() {
    for (auto& ptr : _buckets) {
        while (ptr != nullptr) {
            ptr = ptr->next;
        }
    }
    _node_size = 0;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(const HashMap<K, M, H>& other):
    HashMap{
        other.begin(),
        other.end(),
        other._buckets.size()
    }
{
    ;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(HashMap<K, M, H>&& other):
    _buckets{std::move(other._buckets)},
    _hash_function{std::move(other._hash_function)},
    _node_size{std::move(other._node_size)}
{
    ;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>& HashMap<K, M, H>::operator=(const HashMap<K, M, H>& other) {
    if (this != &other) {
        clear();
        _buckets.resize(other._buckets.size());
        for (auto& val: other) {
            insert(val);
        }
        _hash_function = other._hash_function;
        _node_size = other._node_size;
    }
    return *this;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>& HashMap<K, M, H>::operator=(HashMap<K, M, H>&& other) {
    if (this != &other) {
        clear();
        _buckets = std::move(other._buckets);
        _hash_function = std::move(other._hash_function);
        _node_size = std::move(other._node_size);
    }
    return *this;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::size_type HashMap<K, M, H>::first_not_empty_bucket() const noexcept {
    for (size_type i = 0; i < _buckets.size(); ++i) {
        if (_buckets[i] != nullptr) {
            return i;
        }
    }
    return _buckets.size(); // all buckets are empty
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::iterator HashMap<K, M, H>::make_iterator(node_ptr node) const noexcept{
    if (node == nullptr) {
        return {};
    }

    bucket_array_type* bucket_array_ptr = const_cast<bucket_array_type*>(&_buckets);
    size_type bucket_index = bucket(node->value.first);
    return {bucket_array_ptr, bucket_index, node};
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::begin() noexcept {
    size_type idx = first_not_empty_bucket();
    return idx == _buckets.size()? end() : make_iterator(_buckets[idx]);
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::begin() const noexcept {
    return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->begin());
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::cbegin() const noexcept {
    return begin();
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::end() noexcept {
    return make_iterator(nullptr);
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::end() const noexcept {
    return static_cast<const_iterator>(
        const_cast<HashMap<K, M, H>*>(this)->end()
    );
}


template<typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::cend() const noexcept {
    return end();
}


template<typename K, typename M, typename H>
inline HashMap<K, M, H>::size_type HashMap<K, M, H>::bucket_count() const noexcept {
    return _buckets.size();
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::size_type HashMap<K, M, H>::bucket_size(size_type n) const noexcept {
    size_type count = 0;
    for (auto& ptr = _buckets[n]; ptr != nullptr; ptr = ptr->next) {
        ++count;
    }
    return count;
}


template<typename K, typename M, typename H>
inline HashMap<K, M, H>::size_type HashMap<K, M, H>::bucket(const key_type& key) const noexcept {
    return _hash_function(key) % _buckets.size();
}


template<typename K, typename M, typename H>
inline float HashMap<K, M, H>::load_factor() const noexcept {
    return 1.0 * _node_size / _buckets.size();
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::rehash(size_type count) {
    if (count == 0) {
        throw std::out_of_range("HashMap: rehash count cannot be zero.");
    }
    std::vector<node_ptr> new_buckets(count, nullptr);

    for (auto& ptr : _buckets) {
        while (ptr != nullptr) {
            size_type index = _hash_function(ptr->value.first) % new_buckets.size();
            node_ptr origin = ptr;
            ptr = ptr->next;
            origin->next = new_buckets[index];
            new_buckets[index] = origin;
        }
    }

    _buckets = std::move(new_buckets);
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::reserve(size_type count) {
    _buckets.reserve(count);
}


template<typename K, typename M, typename H>
inline HashMap<K, M, H>::hasher HashMap<K, M, H>::hash_function() const noexcept {
    return _hash_function;
}


template<typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() const noexcept {
    return _node_size == 0;
}


template<typename K, typename M, typename H>
inline HashMap<K, M, H>::size_type HashMap<K, M, H>::size() const noexcept {
    return _node_size;
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::clear() noexcept {
    for (auto& ptr : _buckets) {
        ptr = nullptr;
    }
    _node_size = 0;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::node_ptr_pair HashMap<K, M, H>::_find(const key_type& key) const {
    size_type index = bucket(key);
    node_ptr curr, prev;
    for (curr = _buckets[index], prev = _buckets[index]; curr != nullptr && curr->value.first != key; prev = curr, curr = curr->next)
        ;
    return {prev, curr};
}


template<typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert(const_reference value) {
    auto [_, curr] = _find(value.first);
    if (curr != nullptr) {
        return {make_iterator(curr), false};
    }

    node_ptr inserted_node = node_ptr{new node{value.first, value.second}};

    size_type index = bucket(value.first);
    _buckets[index] = inserted_node;
    ++_node_size;
    _adjust();
    return {make_iterator(inserted_node), true};
}


template<typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert(rv value) {
    auto [_, curr] = _find(value.first);
    if (curr != nullptr) {
        return {make_iterator(curr), false};
    }

    node_ptr inserted_node = node_ptr{new node{std::move(value.first), std::move(value.second)}};

    size_type index = bucket(value.first);
    inserted_node->next = _buckets[index];
    _buckets[index] = inserted_node;
    ++_node_size;
    _adjust();
    return {make_iterator(inserted_node), true};
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::insert(std::initializer_list<value_type> ilist) {
    for (auto& value: ilist) {
        insert(value);
    }
}


template<typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert_or_assign(
    const key_type& key, const mapped_type& obj
) {
    auto [curr, flag] = insert({key, obj});
    if (flag == false) {
        curr->value.second = obj;
    }

    return {make_iterator(curr), flag};
}


template<typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert_or_assign(
    key_type&& key, mapped_type&& obj
) {
    auto [it, flag] = insert({std::move(key), std::move(obj)});
    if (flag == false) {
        it->second = obj;
    }

    return {it, flag};
}


template<typename K, typename M, typename H>
template<typename... Args>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::emplace(Args&&... args) {
    value_type value{std::forward<Args>(args)...};
    return insert(value);
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::iterator HashMap<K, M, H>::erase(const_iterator pos) {
    if (pos == cend()) {
        return end();
    }

    auto [prev, curr] = _find(pos->first);
    if (curr == nullptr) {
        return end();
    }

    if (prev == curr) {
        size_type index = bucket(pos->first);
        assert(_buckets[index] == curr);
        _buckets[index] = _buckets[index]->next;
    } else {
        prev->next = curr->next;
    }
    --_node_size;
    return make_iterator(curr->next);
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::iterator HashMap<K, M, H>::erase(const_iterator first, const_iterator last) {
    for (auto it = first; it != last; ++it) {
        erase(it);
    }
    return last;
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::swap(HashMap<K, M, H>& other) {
    std::swap(_buckets, other._buckets);
    std::swap(_hash_function, other._hash_function);
    std::swap(_node_size, other._node_size);
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::reference HashMap<K, M, H>::at(const key_type& key) {
    auto [prev, curr] = _find(key);
    if (curr == nullptr) {
        throw std::out_of_range("HashMap: key not found.");
    }
    return curr->value;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::const_reference HashMap<K, M, H>::at(const key_type& key) const {
    return static_cast<const_reference>(
        const_cast<HashMap<K, M, H>*>(this)->at(key)
    );
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::mapped_type& HashMap<K, M, H>::operator[](const key_type& key) {
    auto [it, flag] = insert_or_assign(key, mapped_type{});
    return it->second;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::mapped_type& HashMap<K, M, H>::operator[](key_type&& key) {
    auto [it, flag] = insert_or_assign(std::move(key), mapped_type{});
    return it->second;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::size_type HashMap<K, M, H>::count(const key_type& key) const {
    size_type cnt = 0;
    for (auto it = begin(); it != end(); ++it) {
        if (it->first == key) {
            ++cnt;
        }
    }
    return cnt;
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::iterator HashMap<K, M, H>::find(const key_type& key) {
    auto [prev, curr] = _find(key);
    return curr == nullptr? end() : make_iterator(curr);
}


template<typename K, typename M, typename H>
HashMap<K, M, H>::const_iterator HashMap<K, M, H>::find(const key_type& key) const {
    return static_cast<const_iterator>(
        const_cast<HashMap<K, M, H>*>(this)->find(key)
    );
}


template<typename K, typename M, typename H>
bool HashMap<K, M, H>::contains(const key_type& key) const {
    auto [prev, curr] = _find(key);
    return curr != nullptr;
}


template<typename K, typename M, typename H>
bool operator==(const HashMap<K, M, H>& lhs, const HashMap<K, M, H>& rhs) {
    return (
        lhs.size() == rhs.size()
        && std::is_permutation(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
    );
}


template<typename K, typename M, typename H>
inline void HashMap<K, M, H>::_adjust() {
    if (load_factor() > MaxLoadFactor) {
        rehash(_buckets.size() * 2);
    }
}


template<typename K, typename M, typename H>
void HashMap<K, M, H>::inspect() const noexcept {
    std::cout << "===============   HashMap Inspect   ===============" << std::endl;
    std::cout << "HashMap: size = " << _node_size << ", load factor = " << load_factor() << std::endl;
    for (size_type i = 0; i < _buckets.size(); ++i) {
        std::cout << "bucket[" << i << "]: ";
        node_ptr curr = _buckets[i];
        while (curr != nullptr) {
            std::cout << "(" << curr->value.first << ", " << curr->value.second << ") -> ";
            curr = curr->next;
        }
        std::cout << "nullptr" << std::endl;
    }
    std::cout << "===================================================\n" << std::endl;
}


#endif // HASHMAP_HPP