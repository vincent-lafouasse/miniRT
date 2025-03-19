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

#define EXPECT_CAM_EQ(a, b) \
    EXPECT_VEC3_EQ(a.position, b.position); \
    EXPECT_VEC3_EQ(a.direction, b.direction); \
    EXPECT_DOUBLE_EQ(a.fov_deg, b.fov_deg);

#define EXPECT_AMBIENT_EQ(a, b) \
    EXPECT_VEC3_EQ(a.color, b.color); \
    EXPECT_DOUBLE_EQ(a.intensity, b.intensity);

#define EXPECT_POINT_LIGHT_EQ(a, b) \
    EXPECT_VEC3_EQ(a.coordinates, b.coordinates); \
    EXPECT_VEC3_EQ(a.color, b.color); \
    EXPECT_DOUBLE_EQ(a.intensity, b.intensity)

#define EXPECT_SPHERE_EQ(a, b) \
    EXPECT_VEC3_EQ(a.origin, b.origin); \
    EXPECT_VEC3_EQ(a.color, b.color); \
    EXPECT_DOUBLE_EQ(a.radius, b.radius)

TEST(Parser, BasicSceneWithoutHittablesWorks) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n";

    t_camera_specs expected_camera = (t_camera_specs){
        .position = vec3_new(1, 2, 3),
        .direction = vec3_new(1, 0, 0),
        .fov_deg = 90.0,
    };

    t_ambient_light expected_ambient_light = (t_ambient_light){
        .intensity = 0.69,
        .color = rgb_from_elements(4, 5, 6),
    };

    t_point_light expected_point_light = (t_point_light){
        .coordinates = vec3_new(7, 8, 9),
        .intensity = 0.42,
        .color = rgb_from_elements(10, 11, 12),
    };

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    ASSERT_EQ(err, NO_ERROR) << std::format("received error from parse method: {}", error_repr(err));

    EXPECT_CAM_EQ(camera, expected_camera);
    EXPECT_AMBIENT_EQ(scene.ambient_light, expected_ambient_light);
    EXPECT_POINT_LIGHT_EQ(scene.point_light, expected_point_light);

    EXPECT_EQ(scene.objects->len, 0u);
}

TEST(Parser, BasicSceneWithOneSphereWorks) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "sp 55,55,100  6    255,0,127\n";

    t_camera_specs expected_camera = (t_camera_specs){
        .position = vec3_new(1, 2, 3),
        .direction = vec3_new(1, 0, 0),
        .fov_deg = 90.0,
    };

    t_ambient_light expected_ambient_light = (t_ambient_light){
        .intensity = 0.69,
        .color = rgb_from_elements(4, 5, 6),
    };

    t_point_light expected_point_light = (t_point_light){
        .coordinates = vec3_new(7, 8, 9),
        .intensity = 0.42,
        .color = rgb_from_elements(10, 11, 12),
    };

    t_sphere expected_sphere = (t_sphere){
        .origin = vec3_new(55, 55, 100),
        .radius = 6.0 / 2.0,
        .color = rgb_from_elements(255, 0, 127),
    };

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    ASSERT_EQ(err, NO_ERROR) << std::format("received error from parse method: {}", error_repr(err));

    EXPECT_CAM_EQ(camera, expected_camera);
    EXPECT_AMBIENT_EQ(scene.ambient_light, expected_ambient_light);
    EXPECT_POINT_LIGHT_EQ(scene.point_light, expected_point_light);

    ASSERT_EQ(scene.objects->len, 1u);

    ASSERT_EQ(scene.objects->data[0].type, HITTABLE_SPHERE);
    t_sphere sphere = scene.objects->data[0].sphere;
    EXPECT_SPHERE_EQ(sphere, expected_sphere);
}
