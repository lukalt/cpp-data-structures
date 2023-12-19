template<typename T>
void linked_list<T>::push_front(T val) {
    if(head == nullptr) {
        head = tail = new node(val);
        listSize = 1;
    } else {
        auto n = new node(val);
        n->next = head;
        head = n;
        listSize++;
    }
}

template<typename T>
void linked_list<T>::push_back(T val) {
    if(tail == nullptr) {
        head = tail = new node(val);
        listSize = 1;
    } else {
        tail->next = new node(val);
        tail = tail->next;
        listSize++;
    }
}

template<typename T>
void linked_list<T>::removeFirst(T val) {
    node* curr = head;
    node* prev = nullptr;

    while(curr != nullptr) {
        if(curr->val == val) {
            if(prev == nullptr) { // first element in the list
                if(head == tail) { // single-element list
                    tail = curr->next;
                }
                head = curr->next;
            } else {
                if(curr == tail) {
                    tail = nullptr;
                }
                prev->next = curr->next;
            }
            listSize--;
            return;
        }

        prev = curr;
        curr = curr->next;
    }

}

template<typename T>
void linked_list<T>::removeAll(T val) {
    node* curr = head;
    node* prev = nullptr;

    while(curr != nullptr) {
        if(curr->val == val) {
            if(prev == nullptr) { // first element in the list
                if(head == tail) { // single-element list
                    tail = curr->next;
                }
                head = curr->next;
            } else {
                if(curr == tail) {
                    tail = nullptr;
                }
                prev->next = curr->next;
            }
            listSize--;
            node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

template<typename T>
void linked_list<T>::clear()  {
    node* curr = head;
    node* prev = nullptr;
    while(curr != nullptr) {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}
template<typename T>
linked_list<T>::~linked_list()  {
    clear();
}

template<typename T>
T linked_list<T>::get(int index) {
    if(index < 0 || index >= listSize) {
        throw std::invalid_argument(std::to_string(index) + " is out of range [0;" + std::to_string(listSize) + ")");
    }
    node* curr = head;
    int i = 0;
    while(curr != nullptr) {
        if(i == index) {
            return curr->val;
        }
        i++;
        curr = curr->next;
    }
    throw std::invalid_argument(std::to_string(index) + " is out of range [0;" + std::to_string(listSize) + ")");
}

template<typename T>
bool linked_list<T>::contains(T val) {
    node* curr = head;
    while(curr != nullptr) {
        if(curr->val == val) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<typename T>
int linked_list<T>::size() const {
    return listSize;
}

template<typename T>
bool linked_list<T>::empty() const {
    return listSize == 0;
}

template<typename T>
bool linked_list<T>::operator==(const linked_list<T>& other) const {
    node* a = head;
    node* b = other.head;

    while(a != nullptr || b != nullptr) {
        if(a == nullptr || b == nullptr || a->val != b->val) {
            return false;
        }
        a = a->next;
        b = b->next;
    }

    return true;
}

template<typename T>
linked_list<T>& linked_list<T>::operator=(linked_list<T> other) {
    clear();
    for(auto x : other) {
        push_back(x);
    }
    return *this;
}

template<typename T>
linked_list<T>::linked_list(std::initializer_list<T> list) {
    for(auto& x : list) {
        push_back(x);
    }
}

template<typename T>
linked_list<T>::linked_list(T val) {
    push_back(val);
}
