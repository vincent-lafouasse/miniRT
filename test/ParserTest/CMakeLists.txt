file(GLOB_RECURSE parse_module ${TESTED_SRC_DIR}/parse/*.c)

add_executable(ParserTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/parser_test.cpp

	${parse_module}
)

target_include_directories(ParserTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(ParserTest
	libgtest
)
