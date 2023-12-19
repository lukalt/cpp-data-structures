template<typename K, typename V> requires hashable<K>
hash_map<K,V>:: hash_map(int initialCapacity, float loadFactor) : capacity(initialCapacity), loadFactor(loadFactor) {
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

template<typename K, typename V> requires hashable<K>
hash_map<K,V>::hash_map(hash_map<K,V>& copy) {
    capacity = copy.capacity;
    elements = copy.elements;
    loadFactor = copy.loadFactor;
    data = new node*[capacity];
    for(int i = 0; i < capacity; i++) {
        data[i] = nullptr;
        node* curr = copy.data[i];
        while(curr != nullptr) {
            if(data[i] == nullptr) {
                data[i] = new node(curr->key, curr->val);
            } else {
                data[i]->next = new node(curr->key, curr->val);
            }
            curr = curr->next;
        }
    }
}
template<typename K, typename V> requires hashable<K>
int hash_map<K, V>::hashKey(K key) {
    return key % capacity;
}

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
bool hash_map<K, V>::empty() {
    return elements == 0;
}

template<typename K, typename V> requires hashable<K>
int hash_map<K, V>::size() {
    return elements;
}

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
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

template<typename K, typename V> requires hashable<K>
V& hash_map<K, V>::operator[](K key) {
    std::optional<V> opt = get(key);
    if(opt.has_value()) {
        return opt.value();
    }
    throw std::invalid_argument("Map does not contain key");
}

template <typename K, typename V> requires hashable<K>
std::ostream& operator<<(std::ostream& buf, hash_map<K, V>& map) {

    buf << "{";
    bool first {true};
    for(auto [key, val] : map) {
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


template <typename K, typename V> requires hashable<K>
hash_map<K, V>::iterator& hash_map<K,V>::iterator::operator++() {
    while(true) {
        if(nextElement != nullptr) {
            output = nextElement;
            nextElement = nextElement->next;
            return *this;
        }

        if(nextIndex < capacity) {
            nextElement = data[nextIndex];
            nextIndex++;
        } else {
            output = nullptr;
            return *this;
        }
    }
}