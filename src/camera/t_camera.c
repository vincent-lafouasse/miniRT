#include "t_camera.h"

#include <float.h>
#include <math.h>

void construct_viewport(t_vec3 direction,
                        double aspect_ratio,
                        t_vec3* viewport_u_out,
                        t_vec3* viewport_v_out) {
    // set up vaguely towards positive y
    // if colinear to e_y, set to e_x
    // direction really should be normalized for the colinearity check to work
    t_vec3 viewport_up;
    if (fabs(vec3_dot(direction, vec3_new(0.0, 1.0, 0.0))) - 1.0 <
        DBL_EPSILON) {
        viewport_up = vec3_new(1.0, 0.0, 0.0);
    } else {
        viewport_up = vec3_new(0.0, 1.0, 0.0);
    }

    t_vec3 viewport_right = vec3_cross(direction, viewport_up);
    t_vec3 viewport_down = vec3_cross(direction, viewport_right);

    *viewport_v_out = vec3_mul(2.0, viewport_down);
    *viewport_u_out = vec3_mul(2.0 * aspect_ratio, viewport_right);
}

t_camera camera_new(t_point3 position,
                    t_vec3 direction,
                    double fov_deg,
                    size_t screen_width,
                    size_t screen_height) {
    t_vec3 viewport_u;
    t_vec3 viewport_v;
    construct_viewport(direction, (double)screen_width / (double)screen_height,
                       &viewport_u, &viewport_v);
    t_vec3 delta_u = vec3_div(viewport_u, (double)screen_width);
    t_vec3 delta_v = vec3_div(viewport_v, (double)screen_height);

    double fov_radians = M_PI * fov_deg / 180.0;
    double focal_length =
        0.5 * vec3_length(viewport_u) / tan(fov_radians / 2.0);
    t_point3 viewport_center = vec3_mul(focal_length, direction);
    t_point3 viewport_top_left = vec3_sub(
        viewport_center, vec3_mul(0.5, vec3_add(viewport_u, viewport_v)));

    t_point3 pixel00 =
        vec3_add(viewport_top_left, vec3_mul(0.5, vec3_add(delta_u, delta_v)));

    return (t_camera){
        .position = position,
        .pixel00 = pixel00,
        .delta_u = delta_u,
        .delta_v = delta_v,
        .screen_width = screen_width,
        .screen_height = screen_height,
    };
}
