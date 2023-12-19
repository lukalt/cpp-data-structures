#include <gtest/gtest.h>
#include "bst_test.h"
#include "hash_map_test.h"
#include "linked_list_test.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}