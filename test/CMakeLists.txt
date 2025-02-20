cmake_minimum_required(VERSION 3.10)

project(miniRT LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) # LSP stuff, don't worry about it

# fetch gtest
# targets: `libgtest` `libgmock` (static libraries)
include(${CMAKE_SOURCE_DIR}/fetch_gtest.cmake)

# targets: `libft` `libmlx` (static libraries)
include(${CMAKE_SOURCE_DIR}/fetch_libft_mlx.cmake)

set(tested_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/../src/)
set(tested_include_dir ${tested_src_dir}/)

add_subdirectory(DummyTest)

include(CTest)
enable_testing()

add_test(NAME DummyTest
         COMMAND DummyTest)
