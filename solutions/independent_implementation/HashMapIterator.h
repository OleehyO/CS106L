#ifndef HASHMAPITERATOR_H
#define HASHMAPITERATOR_H

#include <vector>
#include <memory>


template<typename Map, bool IsConst=true>
class HashMapIterator {
public:

    using value_type  = std::conditional_t<IsConst, const typename Map::value_type, typename Map::value_type>;
    using node        = Map::node;
    using node_ptr    = Map::node_ptr;
    using size_type   = Map::size_type;

    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference         = value_type&;
    using pointer           = value_type*;
    using bucket_array_type = Map::bucket_array_type;

    friend Map;
    friend class HashMapIterator<Map, true>;
    friend class HashMapIterator<Map, false>;

    HashMapIterator();
    HashMapIterator(bucket_array_type* bucket_array_ptr, size_type bucket_index, node_ptr node = nullptr);
    ~HashMapIterator() = default;

    HashMapIterator(const HashMapIterator<Map, IsConst>& other) = default;
    HashMapIterator(HashMapIterator<Map, IsConst>&& other) = default;

    
    operator HashMapIterator<Map, true>() const noexcept;
    HashMapIterator<Map, IsConst>& operator=(const HashMapIterator<Map, IsConst>& other) = default;
    HashMapIterator<Map, IsConst>& operator=(HashMapIterator<Map, IsConst>&& other) = default;
    
    reference operator*()  const;
    pointer   operator->() const;

    HashMapIterator<Map, IsConst>& operator++();
    HashMapIterator<Map, IsConst>  operator++(int);


    template<typename _Map>
    friend bool operator==(const HashMapIterator<_Map, true>& lhs, const HashMapIterator<_Map, true>& rhs);

    template<typename _Map, bool _IsConst>
    friend bool operator!=(const HashMapIterator<_Map, _IsConst>& lhs, const HashMapIterator<_Map, _IsConst>& rhs);

    
private:
    bucket_array_type* _bucket_array_ptr;

    size_type _bucket_index;
    node_ptr _curr_node;

};


#include "./HashMapIterator.hpp"

#endif // HASHMAPITERATOR_H