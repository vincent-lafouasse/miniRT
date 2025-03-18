#include "gtest/gtest.h"

extern "C" {
#include "parser/parse.h"
};

TEST(Parser, Minimal) {
    const char* minimal =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n";

    t_vec3 expected_camera_position = vec3_new(1, 2, 3);
    t_vec3 expected_camera_orientation = vec3_new(1, 0, 0);
    std::size_t expected_fov_degrees = 90;

    double expected_ambient_intensity = 0.69;
    t_vec3 expected_ambient_color = vec3_new(4, 5, 6);

    t_vec3 expected_pointlight_position = vec3_new(7, 8, 9);
    double expected_pointlight_intensity = 0.69;
    t_vec3 expected_pointlight_color = vec3_new(10, 11, 12);

    t_camera camera;
    t_scene scene;
}
