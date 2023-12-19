#include <gtest/gtest.h>

#include "../include/hash_map.h"
#include <sstream>

TEST(HashMap, GeneralTest) {
    hash_map<int, int> m;


    m.put(1, 1);
    m.put(2, 3);

    ASSERT_EQ(m.get(3, 42), 42);
    ASSERT_EQ(m.get(1, 42), 1);
    ASSERT_EQ(m.get(1), 1);
    ASSERT_EQ(m.get(2), 3);
    ASSERT_FALSE(m.get(3).has_value());

    ASSERT_TRUE(m.containsKey(1));
    ASSERT_TRUE(m.containsKey(2));
    ASSERT_TRUE(m.containsValue(1));
    ASSERT_TRUE(m.containsValue(3));
    ASSERT_FALSE(m.containsKey(0));
    ASSERT_FALSE(m.containsValue(2));

    ASSERT_EQ(m.size(), 2);
    m.remove(1);
    ASSERT_EQ(m.size(), 1);
    ASSERT_FALSE(m.containsKey(1));
    ASSERT_TRUE(m.containsKey(2));

    m.clear();
    ASSERT_TRUE(m.empty());
    ASSERT_EQ(m.size(), 0);
    ASSERT_FALSE(m.containsKey(2));
}

TEST(HashMap, TestCollisions) {
    hash_map<int, int> m;
    for(int i = 0; i < 200; i+=10) {
        m.put(i, i/10);
    }
    ASSERT_EQ(m.size(), 20);
    ASSERT_EQ(m.get(0), 0);
    ASSERT_EQ(m.get(10), 1);
    ASSERT_EQ(m.get(20), 2);
    m.put(11, 1);
    ASSERT_EQ(m.size(), 21);

}
TEST(HashMap, TestSize) {
    hash_map<int, int> m;
    ASSERT_EQ(m.size(), 0);
    m.put(1, 2);
    m.put(3, 2);
    m.put(3, 4);
    ASSERT_EQ(m.size(), 2);
    m.remove(1);
    ASSERT_EQ(m.size(), 1);
    m.remove(2);
    ASSERT_EQ(m.size(), 1);
    m.remove(3);
    ASSERT_EQ(m.size(), 0);
    m.put(1, 2);
    m.put(3, 2);
    ASSERT_EQ(m.size(), 2);
    m.clear();
    ASSERT_EQ(m.size(), 0);
}

TEST(HashMap, TestEmpty) {
    hash_map<int, int> m;
    ASSERT_TRUE(m.empty());
    m.put(1, 2);
    m.put(3, 4);
    ASSERT_FALSE(m.empty());
    m.remove(1);
    ASSERT_FALSE(m.empty());
    m.remove(2);
    ASSERT_FALSE(m.empty());
    m.remove(3);
    ASSERT_TRUE(m.empty());
    m.put(1, 2);
    m.put(3, 2);
    ASSERT_FALSE(m.empty());
    m.clear();
    ASSERT_TRUE(m.empty());

}

TEST(HashMap, TestCopy) {
    hash_map<int, int> m;
    m.put(1, 2);
    m.put(3, 7);
    m.put(13, 8);
    m.put(7, 4);

    hash_map<int,int> k(m);
    ASSERT_EQ(m.size(), k.size());
    for(auto [key, val] : m) {
        ASSERT_EQ(val, k.get(key));
    }
    for(auto [key, val] : k) {
        ASSERT_EQ(val, m.get(key));
    }

}

TEST(HashMap, TestIterator) {
    hash_map<int, int> m;
    m.put(1, 2);
    m.put(3, 7);
    m.put(13, 8);
    m.put(7, 4);

    int count = 4;
    for(auto [key,val] : m) {
        if(key == 1) {
            ASSERT_EQ(val, 2);
        } else if(key == 3) {
            ASSERT_EQ(val, 7);
        } else if(key == 13) {
            ASSERT_EQ(val, 8);
        } else if(key == 7) {
            ASSERT_EQ(val, 4);
        } else {
            ASSERT_TRUE(false); // unreachable
        }

        count--;
    }
    ASSERT_EQ(count, 0);
}

TEST(HashMap, TestPrint) {
    {
        hash_map<int, int> m;
        m.put(1, 2);
        m.put(3, 7);
        m.put(13, 8);
        m.put(7, 4);
        std::stringstream ss;
        ss << m;
        ASSERT_EQ(ss.str(), "{1: 2, 3: 7, 13: 8, 7: 4}");
    }

    {
        hash_map<int,int> m {};
        std::stringstream ss;
        ss << m;
        ASSERT_EQ(ss.str(), "{}");

    }

}