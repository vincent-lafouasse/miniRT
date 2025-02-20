set(tested_source
)
list(TRANSFORM tested_source PREPEND ${tested_src_dir}/)

add_executable(DummyTest
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/dummy_test.cpp

	${tested_source}
)

target_include_directories(DummyTest PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${tested_include_dir}
)

target_link_libraries(DummyTest
	libgtest
	libft
)
