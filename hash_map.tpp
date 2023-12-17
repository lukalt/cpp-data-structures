//
// Created by lukas on 16.12.2023.
//


template<typename K, typename V> requires is_hashable_t<K>
int hash_map<K, V>::hashKey(K key) {
    return key % capacity;
}

template<typename K, typename V> requires is_hashable_t<K>
V hash_map<K, V>::get(K key, V def) {
    int hash = hashKey(key);
    node* curr = data[hash];
    while(curr != nullptr) {
        if(curr->key == key) {
            return curr->val;
        }
        curr = curr->next;
    }
    return def;
}

template<typename K, typename V> requires is_hashable_t<K>
std::optional<V> hash_map<K, V>::get(K key) {
    int hash = hashKey(key) % capacity;
    node* curr = data[hash];
    while(curr != nullptr) {
        if(curr->key == key) {
            return {curr->val};
        }
        curr = curr->next;
    }
    return {};
}

template<typename K, typename V> requires is_hashable_t<K>
bool hash_map<K, V>::empty() {
    return elements == 0;
}

template<typename K, typename V> requires is_hashable_t<K>
int hash_map<K, V>::size() {
    return elements;
}

template<typename K, typename V> requires is_hashable_t<K>
void hash_map<K, V>::clear() {
    for(int i = 0; i < capacity; i++) {
        node* curr = data[i];
        while(curr != nullptr) {
            auto prev = curr;
            curr = curr->next;
            delete prev;
        }
        data[i] = nullptr;
    }
    elements = 0;
}

template<typename K, typename V> requires is_hashable_t<K>
void hash_map<K, V>::remove(K key) {

    int hash = hashKey(key);
    node* curr = data[hash];
    node* prev = nullptr;

    while(curr != nullptr) {
        if (curr->key == key) {
            if(prev == nullptr) {
                data[hash] = curr->next;
            }
            auto toDel = curr;
            curr = curr->next;
            elements--;
            delete toDel;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

template<typename K, typename V> requires is_hashable_t<K>
bool hash_map<K, V>::containsValue(V val) {
    if(elements == 0) {
        return false;
    }
    for(int i = 0; i < capacity; i++) {
        node* curr = data[i];
        while(curr != nullptr) {
            if(curr->val == val) {
                return true;
            }
            curr = curr->next;
        }
    }
    return false;
}

template<typename K, typename V> requires is_hashable_t<K>
bool hash_map<K, V>::containsKey(K key) {
    if(elements == 0) {
        return false;
    }
    int hash = hashKey(key);
    node* curr = data[hash];

    while(curr != nullptr) {
        if (curr->key == key) {
            return true;
        } else {
            curr = curr->next;
        }
    }
    return false;
}

template<typename K, typename V> requires is_hashable_t<K>
void hash_map<K, V>::put(K key, V val) {
    int hash = hashKey(key);
    node* curr = data[hash];
    node* prev = nullptr;
    while(curr != nullptr) {
        if(curr->key == key) {
            curr->val = val;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    node* newNode = new node(key, val);
    if(prev == nullptr) {
        data[hash] = newNode;
    } else {
        prev->next = newNode;
    }

    elements++;
}

template<typename K, typename V> requires is_hashable_t<K>
V& hash_map<K, V>::operator[](K key) {
    std::optional<V> opt = get(key);
    if(opt.has_value()) {
        return opt.value();
    }
    throw std::invalid_argument("Map does not contain key");
}
