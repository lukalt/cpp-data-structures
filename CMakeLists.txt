cmake_minimum_required(VERSION 3.22)
project(data_structures)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE on)
add_compile_options(-gdwarf-4)
add_executable(linked_list_test linked_list_test.cpp)
target_link_libraries(linked_list_test GTest::gtest_main)
add_executable(hash_map_test hash_map_test.cpp)
target_link_libraries(hash_map_test GTest::gtest_main)
add_executable(bst_test bst_test.cpp)
target_link_libraries(bst_test GTest::gtest_main)