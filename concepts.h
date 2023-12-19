#pragma once
#include <iostream>
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
concept is_hashable_t = requires(T t, T t2) {
    t % 10;
    t == t2;
    t != t2;
};
template <typename T>
concept is_comparable_v = requires(T t1, T t2) {
    t1 < t2;
    t1 <= t2;
    t1 == t2;
    t1 != t2;
    t1 > t2;
    t2 >= t1;
};
