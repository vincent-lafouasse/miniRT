set(tested_source
)
list(TRANSFORM tested_source PREPEND ${TESTED_SRC_DIR}/)

add_executable(DummyTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/dummy_test.cpp

	${tested_source}
)

target_include_directories(DummyTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TESTED_INCLUDE_DIR}
)

target_link_libraries(DummyTest
	libgtest
	libft
)
