#include "t_sphere.h"
#include "t_hittable.h"
#include "math/t_interval/t_interval.h"

bool sphere_hit(t_sphere sphere, t_point3 ray_origin, t_vec3 ray_direction) {
    t_vec3 o_c = vec3_sub(sphere.origin, ray_origin);

    double a = vec3_dot(ray_direction, ray_direction);
    double b = -2.0 * vec3_dot(ray_direction, o_c);
    double c = vec3_dot(o_c, o_c) - sphere.radius * sphere.radius;

    double delta = b * b - 4.0 * a * c;

    return delta >= 0.0;
/*
    let o_c = self.origin - ray.origin;

    let a = ray.direction.dot(ray.direction);
    let b = -2.0 * ray.direction .dot (o_c);
    let c = (o_c).dot(o_c) - self.radius * self.radius;

    let discriminant = (b * b) - 4.0 * a * c;

    if discriminant < 0.0 {
        return None;
    }
    let x0 = (-b - discriminant.sqrt()) / (2.0*a);
    let x1 = (-b + discriminant.sqrt()) / (2.0*a);
    let possible_hit = if range.contains(&x0) {
        Some(x0)
} else if range.contains(&x1) {
        Some(x1)
} else {
    None
};
    possible_hit.map(|t| {
            let intersection = ray.at(t);
            let mut normal = (intersection - self.origin).normalized();
            let from_within = (ray.direction.dot(normal) > 0.0);
            if from_within {
                    normal = -normal;
            };
            HitRecord { t, normal, from_within, at: intersection }
    })
    */
}