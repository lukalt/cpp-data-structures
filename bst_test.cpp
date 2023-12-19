#include <gtest/gtest.h>
#include "bst.h"


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#define ASSERT_VALID(tree) ASSERT_TRUE(tree.isValid() )

struct SampleBST : public testing::Test {
    bst<int,int> tree;
    int initialSize {-1};
    void SetUp() override {
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
        initialSize = tree.size();
    }

    void TearDown() override {

    }
};
struct EmptyBST : public testing::Test {
    bst<int,int> tree {};
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SampleBST, RemoveExistingRight) {
    tree.remove(15);

    ASSERT_FALSE(tree.contains(15));
    ASSERT_TRUE(tree.contains(12));
    ASSERT_TRUE(tree.contains(17));
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), initialSize - 1);
}
TEST_F(SampleBST, RemoveExistingLeft) {
    tree.remove(5);

    ASSERT_FALSE(tree.contains(5));
    ASSERT_TRUE(tree.contains(2));
    ASSERT_TRUE(tree.contains(7));
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), initialSize - 1);
}
TEST_F(SampleBST, RemoveRoot) {
    tree.remove(20);

    ASSERT_FALSE(tree.contains(20));
    ASSERT_TRUE(tree.contains(15));
    ASSERT_TRUE(tree.contains(25));
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), initialSize - 1);
}
TEST_F(SampleBST, RemoveLeaf) {
    tree.remove(37);
    ASSERT_FALSE(tree.contains(37));
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), initialSize - 1);
}
TEST_F(SampleBST, RemoveNonExisting) {
    tree.remove(16);

    ASSERT_FALSE(tree.contains(16));
    ASSERT_VALID(tree);
    ASSERT_EQ(tree.size(), initialSize);
}
TEST_F(SampleBST, RemoveLeftSubtreeDownwards) {
    tree.remove(10);
    tree.remove(5);
    tree.remove(15);
    tree.remove(2);
    tree.remove(7);
    tree.remove(12);
    tree.remove(17);
    ASSERT_EQ(tree.size(), initialSize - 7);
    ASSERT_VALID(tree);
}
TEST_F(SampleBST, RemoveLeftSubtreeUpwars) {

    tree.remove(12);
    tree.remove(17);
    tree.remove(2);
    tree.remove(7);
    tree.remove(5);
    tree.remove(15);
    tree.remove(10);
    ASSERT_EQ(tree.size(), initialSize - 7);
    ASSERT_VALID(tree);
}
TEST_F(SampleBST, RemoveAll) {
    std::vector<int> keys {};
    for(auto [key,val] : tree) {
        keys.push_back(key);
    }
    for(auto& key : keys) {
        tree.remove(key);
    }

    for(auto& key : keys) {
        ASSERT_FALSE(tree.contains(key));
    }
    ASSERT_VALID(tree);
    ASSERT_TRUE(tree.empty());
}
TEST_F(SampleBST, Clear) {
    tree.clear();
    ASSERT_TRUE(tree.empty());
    ASSERT_VALID(tree);
}

TEST_F(EmptyBST, IteratorEmpty) {
    ASSERT_TRUE(tree.empty());
    for(auto [key,val] : tree) {
        ASSERT_FALSE(true);
    }
}

TEST_F(EmptyBST, InorderPrintEmpty) {
    std::stringstream ss;
    ss << tree;
    ASSERT_EQ(ss.str(), "{}");
}
TEST_F(SampleBST, InorderPrintSample) {
    std::stringstream ss;
    ss << tree;
    ASSERT_EQ(ss.str(), "{2: 0,5: 0,7: 0,10: 0,12: 0,15: 0,17: 0,20: 0,22: 0,25: 0,27: 0,30: 0,32: 0,35: 0,37: 0}");
}

TEST_F(SampleBST, IteratorFull) {
    std::vector<int> keys = {2,5,7,10,12,15,17,20,22,25,27,30,32,35,37};
    int i = 0;
    for(auto [key,val] : tree) {
        ASSERT_EQ(key, keys[i]);
        i++;
    }
    i = 0;
    for(auto it = tree.begin(); it != tree.end(); it++) {
        pair<int, int> curr = *it;
        ASSERT_EQ(keys[i], curr.first);
        i++;
    }
}