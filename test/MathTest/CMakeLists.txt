message(TESTED_INCLUDE_DIR="${TESTED_INCLUDE_DIR}")

set(tested_source
	math/t_vec3/t_vec3.c
	math/t_vec3/t_vec3.h
)
list(TRANSFORM tested_source PREPEND ${TESTED_SRC_DIR}/)

message(-- tested_source="${tested_source}")

add_executable(ParserTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/parser_test.cpp

	${tested_source}
)

target_include_directories(ParserTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(ParserTest
	libgtest
)
