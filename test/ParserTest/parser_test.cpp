#include "gtest/gtest.h"

#include <format>

extern "C" {
#include "error/t_error.h"
#include "parser/parse.h"
};

#define EXPECT_VEC3_EQ(a, b) \
    EXPECT_DOUBLE_EQ(a.x, b.x); \
    EXPECT_DOUBLE_EQ(a.y, b.y); \
    EXPECT_DOUBLE_EQ(a.z, b.z);

TEST(Parser, BasicSceneWithoutHittablesWorks) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n";

    t_point3 expected_camera_position = vec3_new(1, 2, 3);
    t_vec3 expected_camera_direction = vec3_new(1, 0, 0);
    double expected_fov_degrees = 90.0;

    double expected_ambient_intensity = 0.69;
    t_rgb expected_ambient_color = rgb_from_elements(4, 5, 6);

    t_point3 expected_point_light_coordinates = vec3_new(7, 8, 9);
    double expected_point_light_intensity = 0.42;
    t_rgb expected_point_light_color = rgb_from_elements(10, 11, 12);

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    ASSERT_EQ(err, NO_ERROR) << std::format("received error from parse method: {}", error_repr(err));

    EXPECT_VEC3_EQ(camera.position, expected_camera_position);
    EXPECT_DOUBLE_EQ(camera.fov_deg, expected_fov_degrees);
    EXPECT_VEC3_EQ(camera.direction, expected_camera_direction);

    EXPECT_DOUBLE_EQ(scene.ambient_light.intensity, expected_ambient_intensity);
    EXPECT_VEC3_EQ(scene.ambient_light.color, expected_ambient_color);

    EXPECT_VEC3_EQ(scene.point_light.coordinates, expected_point_light_coordinates);
    EXPECT_DOUBLE_EQ(scene.point_light.intensity, expected_point_light_intensity);
    EXPECT_VEC3_EQ(scene.point_light.color, expected_point_light_color);

    EXPECT_EQ(scene.objects->len, 0);
}

TEST(Parser, BasicSceneWithOneSphereWorks) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "sp 55,55,100  6    255,0,127\n";

    t_point3 expected_camera_position = vec3_new(1, 2, 3);
    t_vec3 expected_camera_direction = vec3_new(1, 0, 0);
    double expected_fov_deg = 90.0;

    double expected_ambient_intensity = 0.69;
    t_rgb expected_ambient_color = rgb_from_elements(4, 5, 6);

    t_point3 expected_point_light_coordinates = vec3_new(7, 8, 9);
    double expected_point_light_intensity = 0.42;
    t_rgb expected_point_light_color = rgb_from_elements(10, 11, 12);

    t_point3 expected_sphere_origin = vec3_new(55, 55, 100);
    double expected_sphere_diameter = 6.0;
    t_rgb expected_sphere_color = rgb_from_elements(255, 0, 127);

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    ASSERT_EQ(err, NO_ERROR) << std::format("received error from parse method: {}", error_repr(err));

    EXPECT_VEC3_EQ(camera.position, expected_camera_position);
    EXPECT_DOUBLE_EQ(camera.fov_deg, expected_fov_deg);
    EXPECT_VEC3_EQ(camera.direction, expected_camera_direction);

    EXPECT_DOUBLE_EQ(scene.ambient_light.intensity, expected_ambient_intensity);
    EXPECT_VEC3_EQ(scene.ambient_light.color, expected_ambient_color);

    EXPECT_VEC3_EQ(scene.point_light.coordinates, expected_point_light_coordinates);
    EXPECT_DOUBLE_EQ(scene.point_light.intensity, expected_point_light_intensity);
    EXPECT_VEC3_EQ(scene.point_light.color, expected_point_light_color);

    ASSERT_EQ(scene.objects->len, 1);

    ASSERT_EQ(scene.objects->data[0].type, HITTABLE_SPHERE);
    t_sphere sphere = scene.objects->data[0].sphere;

    EXPECT_VEC3_EQ(sphere.origin, expected_sphere_origin);
    EXPECT_DOUBLE_EQ(sphere.radius, expected_sphere_diameter / 2.0);
    EXPECT_VEC3_EQ(sphere.color, expected_sphere_color);
}
