#include <gtest/gtest.h>

#include "hash_map.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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

TEST(HashMap, TestIterator) {
    hash_map<int, int> m;
    m.put(1, 2);
    m.put(3, 7);
    m.put(13, 8);
    m.put(7, 4);

    for(auto x : m) {
        std::cout << std::get<0>(x) << std::get<1>(x) << std::endl;
    }

}