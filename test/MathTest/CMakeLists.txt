message(TESTED_INCLUDE_DIR="${TESTED_INCLUDE_DIR}")

set(tested_source
		math/t_tuple4.c
		math/t_tuple4.h
		math/t_point3.c
		math/t_point3.h
		math/t_vec3.c
		math/t_vec3.h
)
list(TRANSFORM tested_source PREPEND ${TESTED_SRC_DIR}/)

message(tested_source="${tested_source}")

add_executable(MathTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/math_test.cpp

	${tested_source}
)

target_include_directories(MathTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(MathTest
	libgtest
)
