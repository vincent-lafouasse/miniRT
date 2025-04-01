message(TESTED_INCLUDE_DIR="${TESTED_INCLUDE_DIR}")

file(GLOB_RECURSE math_module ${TESTED_SRC_DIR}/math/*.c)
file(GLOB_RECURSE ray_module ${TESTED_SRC_DIR}/ray/*.c)
file(GLOB_RECURSE scene_module ${TESTED_SRC_DIR}/scene/*.c)
set(camera_module
	${TESTED_SRC_DIR}/camera/camera_new.c
	${TESTED_SRC_DIR}/camera/t_camera.h
	${TESTED_SRC_DIR}/camera/cast_rays.c
)

message(-- tested_source="${tested_source}")

add_executable(CameraTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/camera_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector.hpp

	${math_module}
	${ray_module}
	${scene_module}
	${camera_module}
)

target_include_directories(CameraTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(CameraTest
	libgtest
)
