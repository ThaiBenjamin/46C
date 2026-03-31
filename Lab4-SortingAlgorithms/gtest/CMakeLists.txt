cmake_minimum_required(VERSION 3.10)

include(FetchContent)

find_package(GTest QUIET)

if (NOT GTest_FOUND)
    message(STATUS "GTest not found, fetching googletest...")
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

set(TEST_SOURCES
    tests_sorters.cpp
)

add_executable(test_lab ${TEST_SOURCES})

# Include headers from project
target_include_directories(test_lab PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

# Reuse project source files except main.cpp
file(GLOB PROJECT_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/../src/*.cpp)
list(REMOVE_ITEM PROJECT_SRC ${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(test_lab PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(test_lab PRIVATE /W4 /permissive-)
endif()

# Link project sources
target_sources(test_lab PRIVATE ${PROJECT_SRC})

if (GTest_FOUND)
    target_link_libraries(test_lab PRIVATE GTest::gtest GTest::gtest_main)
else()
    target_link_libraries(test_lab PRIVATE gtest gtest_main)
endif()

include(GoogleTest)

gtest_discover_tests(test_lab)
