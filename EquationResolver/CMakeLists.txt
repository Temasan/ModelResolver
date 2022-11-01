cmake_minimum_required(VERSION 3.20)
project(EquationResolver)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)
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
        tests/TypedEquationNodeTests.cpp tests/EquationFabricTest.cpp header/EquationMaking/EquationCreator.h header/EquationNodes/NamedEquationNode.h)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(EquationResolver_unit_tests ${Boost_LIBRARIES})
endif()



target_link_libraries(EquationResolver_unit_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(EquationResolver_unit_tests)