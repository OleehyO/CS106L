#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include "./HashMapIterator.h"


template<typename K, typename M, typename H = std::hash<K>>
class HashMap {
public:
    using key_type = K;                          using mapped_type = M;
    using value_type = std::pair<const K, M>;    using size_type = std::size_t;
    using reference = value_type&;               using const_reference = const value_type&;
    using rv = value_type&&;

    using pointer = value_type*;                 using const_pointer = const value_type*;
    using difference_type = std::ptrdiff_t;      using hasher = H;

    using iterator       = HashMapIterator<HashMap, false>;
    using const_iterator = HashMapIterator<HashMap, true>;

    friend class HashMapIterator<HashMap, false>;
    friend class HashMapIterator<HashMap, true>;

    explicit HashMap(size_type nbuckets = InitialBucketSize, const H& hasher = H{});

    template<typename InputIt>
    HashMap(InputIt first, InputIt last, size_type nbuckets = InitialBucketSize, const H& hasher = H{});

    ~HashMap();

    HashMap(const HashMap<K, M, H>& other);
    HashMap(HashMap<K, M, H>&& other);

    HashMap<K, M, H>& operator=(const HashMap<K, M, H>& other);
    HashMap<K, M, H>& operator=(HashMap<K, M, H>&& other);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    inline size_type bucket_count() const noexcept;
    size_type bucket_size(size_type n) const noexcept;
    inline size_type bucket(const key_type& key) const noexcept;

    inline float load_factor() const noexcept;
    void rehash(size_type count);
    void reserve(size_type count);
    inline hasher hash_function() const noexcept;

    inline bool empty() const noexcept;
    inline size_type size() const noexcept;

    void clear() noexcept;
    std::pair<iterator, bool> insert(const_reference value);
    std::pair<iterator, bool> insert(rv value);
    void insert(std::initializer_list<value_type> ilist);
    
    std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj);
    std::pair<iterator, bool> insert_or_assign(key_type&& key, mapped_type&& obj);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);  // 一次插入一个元素

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void swap(HashMap<K, M, H>& other);

    reference at(const key_type& key);
    const_reference at(const key_type& key) const;

    mapped_type& operator[](const key_type& key);
    mapped_type& operator[](key_type&& key);

    size_type count(const key_type& key) const;

    iterator find(const key_type& key);
    const_iterator find(const key_type& key) const;

    bool contains(const key_type& key) const;
    friend bool operator==(const HashMap<K, M, H>& lhs, const HashMap<K, M, H>& rhs);

    void inspect() const noexcept;

private:
    struct node {
        using node_ptr = std::shared_ptr<node>;

        value_type value;
        node_ptr next;

        node(key_type&& key, mapped_type&& obj):
            value{std::move(key), std::move(obj)},
            next{nullptr}
        {
            ;
        }

        node(const key_type& key, const mapped_type& obj):
            value{key, obj},
            next{nullptr}
        {
            ;
        }
    };
    
    using node_ptr       = node::node_ptr;
    using node_ptr_pair  = std::pair<node_ptr, node_ptr>;

    std::vector<node_ptr> _buckets;
    using bucket_array_type = decltype(_buckets);

    hasher _hash_function;

    size_type _node_size;

    static constexpr size_type InitialBucketSize = 4;
    static constexpr float MaxLoadFactor = 0.75;

    size_type first_not_empty_bucket() const noexcept;
    iterator make_iterator(node_ptr node) const noexcept;
    node_ptr_pair _find(const key_type& key) const;
    inline void _adjust();
};

#include "./HashMap.hpp"
#endif  // HASHMAP_H