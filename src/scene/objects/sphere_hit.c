#include "t_sphere.h"
#include "t_hittable.h"
#include "math/t_interval/t_interval.h"

#include <stddef.h>

bool sphere_hit(t_sphere sphere, t_interval range, t_ray ray, t_hit_record *rec) {
    t_vec3 o_c = vec3_sub(sphere.origin, ray.origin);

    double a = vec3_dot(ray.direction, ray.direction);
    double b = -2.0 * vec3_dot(ray.direction, o_c);
    double c = vec3_dot(o_c, o_c) - sphere.radius * sphere.radius;

    double delta = b * b - 4.0 * a * c;

    if (delta < 0.0) {
        return false;
    }

    double x0 = (-b - sqrt(delta)) / (2.0 * a);
    double x1 = (-b + sqrt(delta)) / (2.0 * a);

    if (interval_contains(range, x0)) {
        t_point3 hit = ray_at(ray, x0);
        *rec = (t_hit_record) {
            .point = hit,
            .t = x0,
            .normal = vec3_normalize(vec3_sub(hit, sphere.origin)),
        };
        return true;
    }

    if (interval_contains(range, x1)) {
        t_point3 hit = ray_at(ray, x1);
        *rec = (t_hit_record) {
            .point = hit,
            .t = x1,
            .normal = vec3_normalize(vec3_sub(hit, sphere.origin)),
        };
        return true;
    }

    return false;
}
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