cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

set(DS_PROJECT_NAME data_structures)
set(DS_SOURCE_DIR src)
set(DS_INCLUDE_DIR include)
set(DS_TEST_DIR test)
set(DS_SOURCE ${DS_SOURCE_DIR}/main.cpp)
set(DS_TEST_SOURCE ${DS_TEST_DIR}/test_main.cpp)

project(${DS_PROJECT_NAME})

#########
# GTest #
#########
enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(CMAKE_VERBOSE_MAKEFILE on)
add_compile_options(-gdwarf-4)

include_directories(${DS_SOURCE_DIR})
include_directories(${DS_INCLUDE_DIR})
include_directories(${DS_TEST_DIR})

add_library(${DS_PROJECT_NAME} ${DS_SOURCE_DIR}/main.cpp)
add_executable(${DS_PROJECT_NAME}_test ${DS_TEST_SOURCE})

target_link_libraries(${DS_PROJECT_NAME}_test GTest::gtest_main ${DS_PROJECT_NAME})