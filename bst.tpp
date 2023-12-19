#include "bst.h"

template<typename K, typename V>
requires is_comparable_v<K>
int bst<K, V>::size() {
    return numElements;
}

template<typename K, typename V>
requires is_comparable_v<K>
bool bst<K, V>::empty() {
    return numElements == 0;
}

template<typename K, typename V>
requires is_comparable_v<K>
bool bst<K, V>::contains(K key) {
    return get(key).has_value();
}

template<typename K, typename V>
requires is_comparable_v<K>
void bst<K, V>::clearSubtree(node *node) {
    if (node == nullptr) {
        return;
    }
    clearSubtree(node->left);
    clearSubtree(node->right);
    delete node;
}

template<typename K, typename V>
requires is_comparable_v<K>
void bst<K, V>::clear() {
    clearSubtree(root);
    root = nullptr;
    numElements = 0;
}

template<typename K, typename V>
requires is_comparable_v<K>
void bst<K, V>::remove(K key) {
    node *curr = root;
    node *prev = nullptr;
    node **parentPtr = &root;
    while (curr != nullptr) {
        if (curr->key == key) {
            break;
        } else if (curr->key < key) {
            prev = curr;
            parentPtr = &curr->right;
            curr = curr->right;
        } else {
            prev = curr;
            parentPtr = &curr->left;
            curr = curr->left;
        }
    }
    if (curr == nullptr) {
        return;
    }

    numElements--;

    node *left = curr->left;
    node *right = curr->right;
    if (left == nullptr && right == nullptr) { // element is a leaf
        *parentPtr = nullptr;
    } else if (left != nullptr && right != nullptr) {
        if (right->left == nullptr) {
            *parentPtr = right;
            right->left = left;
        } else {
            node *succ = right;
            node *succParent = curr;
            while (succ->left != nullptr) { // find direct successor
                succParent = succ;
                succ = succ->left;
            }
            succParent->left = succ->right;

            // swap curr and successor
            *parentPtr = succ;
            succ->left = left;
            succ->right = right;

        }
    } else if (left != nullptr) {
        *parentPtr = left;
    } else {
        *parentPtr = right;
    }
    delete curr;
}

template<typename K, typename V>
requires is_comparable_v<K>
bool bst<K, V>::isValid(bst<K, V>::node *node, int min, bool minPresent, int max, bool maxPresent) {
    if (node == nullptr) {
        return true;
    }
    if (minPresent && node->key <= min) {
        return false;
    }
    if (maxPresent && node->key >= max) {
        return false;
    }


    return isValid(node->left, min, minPresent, node->key, true)
           && isValid(node->right, node->key, true, max, maxPresent);
}

template<typename K, typename V>
requires is_comparable_v<K>
bool bst<K, V>::isValid() {
    if (root == nullptr) {
        return true;
    }
    return isValid(root, 0, false, 0, false);
}

template<typename K, typename V>
requires is_comparable_v<K>
void bst<K, V>::insert(K key, V value) {
    node *curr = root;
    node *prev = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value;
            return;
        } else if (curr->key < key) {
            prev = curr;
            curr = curr->right;
        } else {
            prev = curr;
            curr = curr->left;
        }
    }
    node *node = new bst<K, V>::node(key, value);
    if (prev == nullptr) {
        root = node;
    } else if (prev->key < key) {
        prev->right = node;
    } else {
        prev->left = node;
    }

    numElements++;
}

template<typename K, typename V>
requires is_comparable_v<K>
std::optional<V> bst<K, V>::get(K key) {
    node *curr;
    node* parent;
    findNode(key, &curr, &parent);
    if(curr != nullptr) {
        return {curr->value};
    }
    return {};
}

template<typename K, typename V>
requires is_comparable_v<K>
V bst<K, V>::get(K key, V val) {
    std::optional<V> opt = get(key);
    if (opt.has_value()) {
        return opt.value();
    }
    return val;
}

template<typename K, typename V>
requires is_comparable_v<K>
std::optional<pair<K, V>> bst<K,V>::findSuccessor(K key) {
    node* curr;
    node* parent;
    findNode(key, &curr, &parent);
    if(curr == nullptr) {
        return {};
    }

    node* succ = curr->right;
    while(succ->left != nullptr) {
        succ = succ->left;
    }
    if(parent != nullptr && parent->key > key && parent->key < succ->key) {
        return parent->toPair();
    }
    return succ->toPair();
}

template<typename K, typename V>
requires is_comparable_v<K>
void bst<K,V>::findNode(K key, class node** node, class node** parent) {
    auto curr = root;
    *parent = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            *node = curr;
            return;
        } else if (curr->key < key) {
            *parent = curr;
            curr = curr->right;
        } else {
            *parent = curr;
            curr = curr->left;
        }
    }
    *node = nullptr;
}

template<typename K, typename V>
requires is_comparable_v<K>
std::optional<pair<K, V>> findPredecessor(K key) {
    return {};
}