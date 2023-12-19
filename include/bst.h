#ifndef DATA_STRUCTURES_BST_H
#define DATA_STRUCTURES_BST_H

#include <type_traits>
#include <optional>
#include <utility>
#include <tuple>
#include <stack>
#include "concepts.h"

using std::pair;

template <typename K, typename V> requires comparable<K>
class bst {
private:
    class node {
    public:
        node* left;
        node* right;
        K key;
        V value;

        node(K key, V value) : key(key), value(value) {
            left = nullptr;
            right = nullptr;
        }

        std::pair<K,V> toPair() {
            return std::make_pair(this->key, this->value);;
        }
    };

    node* root;
    int numElements;

    bool isValid(node* node, int min, bool minPresent, int max, bool maxPresent);

    void clearSubtree(node* node);

    void findNode(K key, class node** node, class node** parent);

public:

    bst() {
        root = nullptr;
        numElements = 0;
    }

    int size();

    bool empty();

    bool contains(K key);

    void remove(K key);

    void insert(K key, V value);

    std::optional<V> get(K key);

    V get(K key, V val);

    void clear();

    bool isValid();

    std::optional<pair<K, V>> findSuccessor(K key);

    std::optional<pair<K, V>> findPredecessor(K key);

    /**
     * Inorder iterator through a BST
     */
    class iterator : public std::iterator<std::input_iterator_tag, pair<K,V>, long, const pair<K,V>*, pair<K,V>&> {
        private:
            std::stack<node*> stack = {};
            node* out;

        public:
        iterator() {
            stack = {};
            out = nullptr;
        }

        explicit iterator(bst<K,V>& bst) {
            node* curr = bst.root;
            while(curr != nullptr) {
                stack.push(curr);
                curr = curr->left;
            }

            (*this)++;
        }

        iterator& operator++() {
            if(stack.empty()) {
                out = nullptr;
                return *this;
            }
            out = stack.top();

            node* curr = out->right;
            stack.pop();

            while(curr != nullptr) {
                stack.push(curr);
                curr = curr->left;
            }

            return *this;
        }

        iterator operator++(int) {
            iterator ret = *this;
            ++(*this);
            return ret;
        }

        bool operator==(iterator other) const {
            return out == nullptr && other.out == nullptr;
        }

        bool operator!=(iterator other) const {
            return out != nullptr || other.out != nullptr;
        }

        pair<K,V> operator*() const {
            std::cout << std::endl;
            if(out == nullptr) {
                throw std::invalid_argument("iterator in invalid state");
            }
            return out->toPair();
        }
    };

    iterator begin() {
        return iterator(*this);
    }

    iterator end() {
        return iterator();
    }

};

template <typename K, typename V> requires comparable<K> and printable<K> and printable<V>
std::ostream& operator<<(std::ostream& buf, bst<K,V>& tree) {
    buf << "{";
    bool first = true;
    for(auto [key, val] : tree) {
        if(first) {
            first = false;
        } else {
            buf << ", ";
        }
        buf << key << ": " << val;
    }
    buf << "}";
    return buf;
}

#include "../src/bst.tpp"
#endif //DATA_STRUCTURES_BST_H
