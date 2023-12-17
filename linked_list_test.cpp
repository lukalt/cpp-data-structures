#include <gtest/gtest.h>

#include "linked_list.h"

#include <vector>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(LinkedList, TestSize) {
    linked_list<int> list;
    ASSERT_EQ(list.size(), 0);
    list = {1};
    ASSERT_EQ(list.size(), 1);
    list.push_back(12);
    ASSERT_EQ(list.size(), 2);
    list.removeAll(12);
    ASSERT_EQ(list.size(), 1);
}

TEST(LinkedList, TestAdd) {
    linked_list<int> list;

    ASSERT_EQ(0, list.size());

    list.push_back(1);
    ASSERT_EQ(1, list.size());
    ASSERT_EQ(1, list.get(0));
    ASSERT_ANY_THROW(list.get(-1));
    ASSERT_ANY_THROW(list.get(1));

    list = {1,2,3,4};
    ASSERT_EQ(list.get(0), 1);
    list.push_front(0);
    ASSERT_EQ(list.get(0), 0);
    ASSERT_EQ(list.get(1), 1);

}

TEST(LinkedList, TestRemove) {
    linked_list<int> list = {1,1,1,2,3,4};
    list.removeFirst(1);

    linked_list<int> ref = {1,1,2,3,4};
    ASSERT_EQ(list, ref);

    list.removeFirst(5);
    ASSERT_EQ(list, ref);
    list.removeAll(5);
    ASSERT_EQ(list, ref);
    list.removeAll(1);
    ref = {2,3,4};
    ASSERT_EQ(list, ref);
    list.removeAll(4);
    ref = {2,3};
    ASSERT_EQ(list, ref);
    list.removeFirst(3);
    ref = {2};
    ASSERT_EQ(list, ref);
    list.removeFirst(2);
    ASSERT_EQ(list.size(), 0);

}

TEST(LinkedList, TestConstructIterable) {
    std::vector<int> x = {1,2,3,4};
    linked_list<int> ref = {1,2,3,4};
    linked_list<int> test = linked_list<int>(x);
    ASSERT_EQ(test, ref);
}

TEST(LinkedList, TestClear) {
    linked_list<int> list = {1,2,3,4};
    ASSERT_EQ(list.size(), 4);
    list.clear();
    ASSERT_EQ(list.size(), 0);
    list.push_back(1);
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.get(0), 1);

}
TEST(LinkedList, TestIterator) {
    std::vector<int> dummy {};
    ASSERT_EQ(dummy.begin(), dummy.end());

    dummy = {1,2,3,4};
    int i = 0;
    for(auto& x : dummy) {
        i++;
        ASSERT_EQ(i, x);
    }

}