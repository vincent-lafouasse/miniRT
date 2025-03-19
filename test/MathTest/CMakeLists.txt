message(TESTED_INCLUDE_DIR="${TESTED_INCLUDE_DIR}")

file(GLOB_RECURSE tested_source ${TESTED_SRC_DIR}/math/*.c)

message(-- tested_source="${tested_source}")

add_executable(MathTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/math_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector.hpp

	${tested_source}
)

target_include_directories(MathTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(MathTest
	libgtest
)
