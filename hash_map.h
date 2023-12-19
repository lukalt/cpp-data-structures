#ifndef DATA_STRUCTURES_HASH_MAP_H
#define DATA_STRUCTURES_HASH_MAP_H
#include <optional>
#include <tuple>
#include "concepts.h"
using std::tuple;

template <typename K, typename V> requires is_hashable_t<K>
class hash_map {
private:
    int capacity;
    int elements {0};
    float loadFactor = 0.75;

    struct node {
        K key;
        V val;
        node* next;

        node(K key, V val) : key(key), val(val), next(nullptr) {};
    };

    node** data;
    int hashKey(K key);

public:
    hash_map(hash_map<K,V>& copy);

    explicit hash_map(int initialCapacity=10, float loadFactor=0.75);

class iterator : public std::iterator<std::input_iterator_tag, tuple<K,V>, long, const tuple<K,V>*, tuple<K,V>&> {
    private:
        const int capacity;
        node** data;
        int nextIndex;
        node* nextElement = nullptr;
        node* output = nullptr;

    public:
        explicit iterator(node**& data, int index, int capacity) : data(data), capacity(capacity), nextIndex(index), nextElement(nullptr) {
            (*this)++;
        }

        iterator& operator++();

        iterator operator++(int) {
            iterator ret = *this;
            ++(*this);
            return ret;
        }

        bool operator==(iterator other) const {
            return output == nullptr && other.output == nullptr && nextIndex >= capacity && other.nextIndex >= other.capacity;
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

        tuple<K,V> operator*() const {
            return std::make_tuple(output->key, output->val);
        }
    };

    ~hash_map() {
        clear();
        delete[] data;
    }

    void put(K key, V val);

    bool containsKey(K key);

    bool containsValue(V val);

    void remove(K key);

    void clear();

    int size();

    bool empty();

    iterator begin() {
        return iterator(data, 0, capacity);
    }

    iterator end() {
        return iterator(data, capacity, capacity);
    }

    std::optional<V> get(K key);

    V get(K key, V def);

    V& operator[](K key);


};

template <typename K, typename V> requires is_hashable_t<K>
std::ostream& operator<<(std::ostream& buf, hash_map<K, V>& map);

#include "hash_map.tpp"

#endif //DATA_STRUCTURES_HASH_MAP_H
