file(GLOB_RECURSE parse_module ${TESTED_SRC_DIR}/parser/*.c)
file(GLOB_RECURSE math_module ${TESTED_SRC_DIR}/math/*.c)
file(GLOB_RECURSE scene_module ${TESTED_SRC_DIR}/scene/*.c)
file(GLOB_RECURSE error_module ${TESTED_SRC_DIR}/error/*.c)

add_executable(ParserTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/parser_test.cpp

	${parse_module}
	${math_module}
	${scene_module}
	${error_module}
)

target_include_directories(ParserTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(ParserTest
	libft
	libgtest
)
