#pragma once
#include <iostream>
template <typename T>
concept printable = requires(T t, std::ostream& buf) {
buf << t;
};
template<typename T, typename I>
concept iterable = requires(I i, T t) {
    i.begin();
    i.end();
    *i.begin();
    *i.end();
};
template <typename T>
concept hashable = requires(T t, T t2) {
    t % 10;
    t == t2;
    t != t2;
};
template <typename T>
concept comparable = requires(T t1, T t2) {
    t1 < t2;
    t1 <= t2;
    t1 == t2;
    t1 != t2;
    t1 > t2;
    t2 >= t1;
};
