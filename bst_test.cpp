#include <gtest/gtest.h>
#include "bst.h"


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#define ASSERT_VALID(tree) ASSERT_TRUE(tree.isValid() )

TEST(BST, Main) {
    bst<int, int> tree {};
    ASSERT_TRUE(tree.empty());
    ASSERT_VALID(tree);

    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(30, 0);
    tree.insert(5, 0);
    tree.insert(15, 0);
    tree.insert(25, 0);
    tree.insert(35, 0);
    tree.insert(2, 0);
    tree.insert(7, 0);
    tree.insert(12, 0);
    tree.insert(17, 0);
    tree.insert(22, 0);
    tree.insert(27, 0);
    tree.insert(32, 0);
    tree.insert(37, 0);
    ASSERT_VALID(tree);
    const int s = 15;
    ASSERT_EQ(tree.size(), s);
    ASSERT_TRUE(tree.contains(15));
    ASSERT_FALSE(tree.contains(14));
    tree.remove(4);
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), s);
    tree.remove(30);
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), s-1);
    ASSERT_FALSE(tree.contains(4));
    tree.insert(4, 0);

    ASSERT_VALID(tree);
    ASSERT_TRUE(tree.contains(4));
    tree.insert(4, 42);

    ASSERT_VALID(tree);
    ASSERT_TRUE(tree.contains(4));
    ASSERT_EQ(tree.get(4), 42);
    ASSERT_EQ(tree.get(30, 42), 42);
    ASSERT_FALSE(tree.contains(30));

    ASSERT_VALID(tree);

    tree.inorderPrint();

    for(auto it = tree.begin(); it != tree.end(); it++) {
        pair<int, int> curr = *it;
        std::cout << curr.first << std::endl;
    }

    for(auto curr : tree) {
        std::cout << curr.first << std::endl;
    }

}

TEST(BST, Iterator) {
    bst<int, int> tree{};
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(30, 0);
    tree.insert(5, 0);
    tree.insert(15, 0);
    tree.insert(25, 0);
    tree.insert(35, 0);

    std::vector<int> keys = {5,10,15,20,25,30,35};
    int i = 0;
    for(auto [key,val] : tree) {
        ASSERT_EQ(key, keys[i]);
        i++;
    }
}