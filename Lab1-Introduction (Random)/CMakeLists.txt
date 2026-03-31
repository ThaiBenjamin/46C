cmake_minimum_required(VERSION 3.14)
project(IntroductionLabCpp)

set(CMAKE_CXX_STANDARD 17)

# Consistent output locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

foreach(OUTPUT_CONFIG Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUT_CONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUT_CONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUT_CONFIG})
endforeach()

add_executable(intro_lab
    src/main.cpp
    src/Bag.cpp
    src/Token.cpp
)

target_include_directories(intro_lab PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- GoogleTest target ---
# We assume GoogleTest is available in the build environment (via system install or toolchain).
# This project layout provides a gtest main at gtest/gtestmain.cpp and test files in gtest/.
file(GLOB GTEST_SOURCES CONFIGURE_DEPENDS gtest/*.cpp)

add_executable(intro_lab_tests
    src/Bag.cpp
    src/Token.cpp
    ${GTEST_SOURCES}
)

target_include_directories(intro_lab_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Try to use a system-installed GoogleTest first; otherwise fetch it.
set(GTEST_FOUND_LOCAL FALSE)

find_package(GTest QUIET CONFIG)
if (GTest_FOUND)
    set(GTEST_FOUND_LOCAL TRUE)
    target_link_libraries(intro_lab_tests PRIVATE GTest::gtest GTest::gtest_main)
else()
    find_package(GTest QUIET)
    if (GTest_FOUND)
        set(GTEST_FOUND_LOCAL TRUE)
        target_link_libraries(intro_lab_tests PRIVATE GTest::gtest GTest::gtest_main)
    endif()
endif()

if (NOT GTEST_FOUND_LOCAL)
    message(STATUS "GTest not found on system; fetching googletest via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    # For Windows: prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Link the targets provided by fetched googletest
    if (TARGET GTest::gtest AND TARGET GTest::gtest_main)
        target_link_libraries(intro_lab_tests PRIVATE GTest::gtest GTest::gtest_main)
    else()
        target_link_libraries(intro_lab_tests PRIVATE gtest gtest_main)
    endif()
endif()