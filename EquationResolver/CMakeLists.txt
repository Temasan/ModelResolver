cmake_minimum_required(VERSION 3.20)
project(EquationResolver)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(EquationResolver_unit_tests
        tests/TypedEquationNodeTests.cpp)

target_link_libraries(EquationResolver_unit_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(EquationResolver_unit_tests)