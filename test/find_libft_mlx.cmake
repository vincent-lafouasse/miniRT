set(libft_dir
  ${LIB_DIR}/libft
)
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES
  IMPORTED_LOCATION "${libft_dir}/libft.a"
  INTERFACE_INCLUDE_DIRECTORIES "${libft_dir}/include"
)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

set(mlx_dir
    ${LIB_DIR}/minilibx-linux
)
add_library(libmlx STATIC IMPORTED)
set_target_properties(libmlx PROPERTIES
  IMPORTED_LOCATION "${mlx_dir}/libmlx.a"
  INTERFACE_INCLUDE_DIRECTORIES "${mlx_dir}"
)
