cmake_minimum_required(VERSION 3.10)

project(miniRT LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) # LSP stuff, don't worry about it

set(CMAKE_C_FLAGS  "-Wall -Wextra")
set(CMAKE_CXX_FLAGS  "-Wall -Wextra")

set(ROOT ${CMAKE_SOURCE_DIR}/..)
set(TESTED_SRC_DIR ${ROOT}/src)
set(TESTED_INCLUDE_DIR ${TESTED_SRC_DIR})

set(LIB_DIR ${ROOT}/lib)

# targets: `libgtest` `libgmock` (static libraries)
include(fetch_gtest.cmake)

set(libft_dir
  ${LIB_DIR}/libft
)
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES
  IMPORTED_LOCATION "${libft_dir}/libft.a"
  INTERFACE_INCLUDE_DIRECTORIES "${libft_dir}/include"
)

add_subdirectory(MathTest)
add_subdirectory(CameraTest)

include(CTest)
enable_testing()

add_test(NAME MathTest
		COMMAND MathTest)
add_test(NAME CameraTest
		COMMAND CameraTest)
