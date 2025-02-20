set(libft_dir
  ${CMAKE_SOURCE_DIR}/../lib/libft
)
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES
  IMPORTED_LOCATION "${libft_dir}/libft.a"
  INTERFACE_INCLUDE_DIRECTORIES "${libft_dir}/include"
)

set(mlx_dir
    ${CMAKE_SOURCE_DIR}/../lib/minilibx-linux
)
add_library(libmlx STATIC IMPORTED)
set_target_properties(libmlx PROPERTIES
  IMPORTED_LOCATION "${mlx_dir}/libmlx.a"
  INTERFACE_INCLUDE_DIRECTORIES "${mlx_dir}"
)
