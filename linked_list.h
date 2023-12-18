#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <iostream>
#include <type_traits>
#include<iostream>

template <typename T>
concept printable_t = requires(T t, std::ostream& buf) {
    buf << t;
};

template<typename T, typename I>
concept iterable_t = requires(I i, T t) {
    i.begin();
    i.end();
    *i.begin();
    *i.end();
};

template <typename T>
class linked_list {
private:
    struct node {
        node* next;
        T val;

        explicit node(T val) : val(val), next(nullptr) {};

        node(T val, node* next) : val(val), next(next) {};
    };

    node* head = nullptr;
    node* tail = nullptr;
    int listSize {0};

public:
class iterator : public std::iterator<std::input_iterator_tag, T, long, const T*, T&> {
private:
    node* curr;
public:
    explicit iterator(node* _curr) : curr(_curr) {}

    iterator& operator++() {
        if(curr == nullptr) {
            throw std::invalid_argument("reached end of list");
        }
        curr = curr->next;
        return *this;
    }

    iterator operator++(int) {
        iterator ret = *this;
        ++(*this);
        return ret;
    }

    bool operator==(iterator other) const {
        return curr == other.curr;
    }

    bool operator!=(iterator other) const {
        return curr != other.curr;
    }

    T operator*() const {
        return curr->val;
    }
};

    linked_list() = default;

    linked_list(std::initializer_list<T> list);

    /**
     *
     * @tparam I
     * @param iterator
     * @param dummy
     */
    template<typename I> requires iterable_t<T, I>
    explicit linked_list(I iterator) {
        for(auto& x : iterator) {
            push_back(x);
        }
    }

    /**
     * Copies another linked list into this list
     * @param copy the list to copy
     */
    linked_list(linked_list<T>& copy) {
        for(auto& x : copy) {
            push_back(x);
        }
    }

    /**
     * Creates a new linked list and initialize it with a single element
     * @param val value to initialize with
     */
    linked_list(T val);

    /**
     * Destructs the list and frees all allocated memory
     */
    ~linked_list();

    /**
     * Inserts an element at the beginning of the list
     * @param val the element to insert
     */
    void push_front(T val);

    /**
     * Inserts an element at the end of the list
     * @param val the element to insert
     */
    void push_back(T val);

    /**
     * Removes the first occurrence of the provided element
     * @param val the element to remove
     */
    void removeFirst(T val);

    /**
     * Removes all occurrences of the provided element
     * @param val the element to remove
     */
    void removeAll(T val);

    /**
     * Checks if the provided element is in the list.
     * @param val Element to look for.
     * @return True, iff. the element is in the list
     */
    bool contains(T val);

    /**
     * Returns the element at the provided index. Indexes start at 0.
     * @param index index to search for
     * @return value
     */
    T get(int index);

    /**
     * Removes all elements in the list
     */
    void clear();

    /**
     * Returns the current size of the list.
     * @return size of the list
     */
    int size() const;

    bool empty() const;

    bool operator==(const linked_list<T>& other) const;

    linked_list<T>& operator=(linked_list<T> other);

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }
};

template<typename T>
linked_list<T> make_linked_list(std::initializer_list<T> initializerList) {
    return linked_list<T>(initializerList);
}


template <printable_t T>
std::ostream& operator<<(std::ostream& buf, linked_list<T>& list) {
    buf << '[';
    bool first = true;
    for(auto v : list) {
        if(first) {
            first = false;
        } else {
            buf << ", ";
        }
        buf << v;
    }
    buf << ']';
    return buf;
}
#endif //DATA_STRUCTURES_LINKED_LIST_H

#include "linked_list.tpp"