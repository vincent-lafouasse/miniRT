message(TESTED_INCLUDE_DIR="${TESTED_INCLUDE_DIR}")

file(GLOB_RECURSE math_module ${TESTED_SRC_DIR}/math/*.c)
file(GLOB_RECURSE camera_module ${TESTED_SRC_DIR}/camera/*.c)

message(-- tested_source="${tested_source}")

add_executable(CameraTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/camera_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector.hpp

	${camera_module}
	${math_module}
)

target_include_directories(CameraTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(CameraTest
	libgtest
)
