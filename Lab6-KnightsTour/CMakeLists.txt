cmake_minimum_required(VERSION 3.10)
project(KnightsTour)

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

# All .cpp files in src/
file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(knightstour ${SRC_FILES})

# Public headers live under include/
target_include_directories(knightstour PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings
if(MSVC)
  target_compile_options(knightstour PRIVATE /W4 /permissive-)
else()
  target_compile_options(knightstour PRIVATE -Wall -Wextra -Wpedantic)
endif()

# -------------------- GoogleTest --------------------
include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  file(GLOB GTEST_SRC CONFIGURE_DEPENDS gtest/*.cpp)
  if(GTEST_SRC)
    # Build tests against project sources (exclude main.cpp)
    file(GLOB PROJ_SRC CONFIGURE_DEPENDS src/*.cpp)
    list(REMOVE_ITEM PROJ_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

    add_executable(knightstour_tests ${GTEST_SRC} ${PROJ_SRC})
    target_include_directories(knightstour_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(knightstour_tests GTest::gtest_main)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
      target_compile_options(knightstour_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    set_target_properties(knightstour_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    include(GoogleTest)
    gtest_discover_tests(knightstour_tests)
  endif()
endif()