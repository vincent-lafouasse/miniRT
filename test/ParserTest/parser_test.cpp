#include "gtest/gtest.h"

extern "C" {
#include "error/t_error.h"
#include "scene/t_scene.h"
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

TEST(Parser, ParseFromFileRejectsNonRtFile) {
    const char* filename = "./balls";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse_from_file(filename, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected fail from parse_from_file, got: " << error_repr(err);
    ASSERT_EQ(err, E_BAD_MAP_SUFFIX) << "received wrong error from parse_from_file method: " << error_repr(err);
}

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
    ASSERT_EQ(err, NO_ERROR) << "received error from parse method: " << error_repr(err);

    EXPECT_CAM_EQ(camera, expected_camera);
    EXPECT_AMBIENT_EQ(scene.ambient_light, expected_ambient_light);
    EXPECT_EQ(scene.point_lights->len, 1);
    EXPECT_POINT_LIGHT_EQ(scene.point_lights->data[0], expected_point_light);

    EXPECT_EQ(scene.objects->len, 0u);

    scene_destroy(&scene);
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
        .color = rgb_from_elements(255, 0, 127),
        .radius = 6.0 / 2.0,
    };

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    ASSERT_EQ(err, NO_ERROR) << "received error from parse method" << error_repr(err);

    EXPECT_CAM_EQ(camera, expected_camera);
    EXPECT_AMBIENT_EQ(scene.ambient_light, expected_ambient_light);
    EXPECT_EQ(scene.point_lights->len, 1);
    EXPECT_POINT_LIGHT_EQ(scene.point_lights->data[0], expected_point_light);

    ASSERT_EQ(scene.objects->len, 1u);

    ASSERT_EQ(scene.objects->data[0].type, HITTABLE_SPHERE);
    t_sphere sphere = scene.objects->data[0].sphere;
    EXPECT_SPHERE_EQ(sphere, expected_sphere);

    scene_destroy(&scene);
}

TEST(Parser, UnknownElementFails) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "sp 55,55,100  6    255,0,127\n"
        "co 55,55,100  6    255,0,127\n";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_UNKNOWN_ELEMENT) << "received wrong error from parse method" << error_repr(err);
}

TEST(Parser, ExtraElementFieldsFails) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "sp 55,55,100  6    255,0,127\n"
        "sp 55,55,100  6 20    255,0,127\n";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_MALFORMATTED_ELEMENT) << "received wrong error from parse method" << error_repr(err);
}

TEST(Parser, EmptyInputFails) {
    const char* input = "";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
}

TEST(Parser, ManyCamerasDoesNotWork) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "C 1,2,3 1,0,0 90\n"
        "sp 55,55,100  6    255,0,127\n";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_MUST_HAVE_ONE_CAMERA) << "received wrong error from parse method" << error_repr(err);
}

TEST(Parser, IllegalPointLightFails) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 1.42 10,11,12\n"
        "sp 55,55,100  6    255,0,127\n";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_OUT_OF_RANGE) << "received wrong error from parse method" << error_repr(err);
}

TEST(Parser, IllegalSphereObjectFails) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "sp 55,55,100  -42    255,0,127\n";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_OUT_OF_RANGE) << "received wrong error from parse method" << error_repr(err);
}

TEST(Parser, IllegalPlaneObjectFails) {
    const char* input =
        "C 1,2,3 1,0,0 90\n"
        "A 0.69 4,5,6\n"
        "L 7,8,9 0.42 10,11,12\n"
        "pl	0,0,0			0,0,0			64,64,64";

    t_camera_specs camera;
    t_scene scene;

    t_error err = parse(input, &camera, &scene);
    EXPECT_NE(err, NO_ERROR) << "expected scene fail" << error_repr(err);
    ASSERT_EQ(err, E_UNEXPECTED_NULL_VECTOR) << "received wrong error from parse method" << error_repr(err);
}
