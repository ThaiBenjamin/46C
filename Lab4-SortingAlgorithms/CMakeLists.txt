cmake_minimum_required(VERSION 3.10)
project(TimingSort_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Consistent output locations: put executables in build/bin and libraries in build/lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# For multi-config generators
foreach(OUTPUT_CONFIG Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUT_CONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUT_CONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUT_CONFIG})
endforeach()

# Sources
file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(TimingSort ${SRC_FILES})

target_include_directories(TimingSort PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(TimingSort PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(TimingSort PRIVATE /W4 /permissive-)
endif()

# Enable and add Google Test-based unit tests (builds into build/bin)
enable_testing()
add_subdirectory(gtest)
