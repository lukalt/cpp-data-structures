//
// Created by lukas on 16.12.2023.
//

#ifndef DATA_STRUCTURES_HASH_MAP_H
#define DATA_STRUCTURES_HASH_MAP_H
#include <optional>
#include <tuple>
using std::tuple;

template <typename T>
concept is_hashable_t = requires(T t, T t2) {
     t % 10;
     t == t2;
     t != t2;
};

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
    hash_map(int initialCapacity=10, float loadFactor=0.75) : capacity(initialCapacity), loadFactor(loadFactor) {
        if(capacity < 1) {
            throw std::invalid_argument("Capacity must be greater than 0.");
        }
        if(loadFactor <= 0 || loadFactor > 1) {
            throw std::invalid_argument("load factor must be greater than 0 and at most 1.0");
        }
        data = new node*[initialCapacity];
        for(int i = 0; i < capacity; i++) {
            data[i] = nullptr;
        }
    }

class iterator : public std::iterator<std::input_iterator_tag, tuple<K,V>, long, const tuple<K,V>*, tuple<K,V>&> {
    private:
        const int capacity;
        node** const data;
        int index;
        node* curr = nullptr;
    public:
        explicit iterator(node** nodes, int capacity) : data(nodes), index(0), capacity(capacity) {
            curr = nodes[0];
        }
        explicit iterator(node** nodes, int capacity, int index, node* curr) : data(nodes), index(index), curr(curr), capacity(capacity) {
        }

        iterator& operator++() {
            while(true) {
                if(curr != nullptr && curr->next != nullptr) {
                    curr = curr->next;
                    return *this;
                }
                if(index >= capacity - 1) {
                    index = capacity;
                    curr = nullptr;
                    return *this;
                }
                index++;
                curr = data[index];
            }
        }

        iterator operator++(int) {
            iterator ret = *this;
            ++(*this);
            return ret;
        }

        bool operator==(iterator other) const {
            if(index >= capacity && other.index >= other.capacity) {
                return true;
            }
            return index == other.index && curr == other.curr;
        }

        bool operator!=(iterator other) const {
            return index != other.index || curr != other.curr;
        }

        tuple<K,V> operator*() const {
            return std::make_tuple(curr->key, curr->val);
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
        return iterator(data, capacity);
    }

    iterator end() {
        return iterator(data, capacity, capacity, nullptr);
    }

    std::optional<V> get(K key);

    V get(K key, V def);

    V& operator[](K key);

};

template <typename K, typename V> requires is_hashable_t<K>
std::ostream& operator<<(std::ostream& buf, hash_map<K, V>) {

    return buf;
}

#include "hash_map.tpp"

#endif //DATA_STRUCTURES_HASH_MAP_H
