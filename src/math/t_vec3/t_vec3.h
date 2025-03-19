#ifndef T_VEC3_H
# define T_VEC3_H

# include <stdbool.h>

struct s_vec3 {
	double x;
	double y;
	double z;
};
typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;

static inline t_vec3	vec3_new(double x, double y, double z) {
	return (t_vec3){.x = x, .y = y, .z = z};
}

t_vec3	vec3_add(t_vec3 self, t_vec3 other);
t_vec3	vec3_sub(t_vec3 self, t_vec3 other);
t_vec3	vec3_mul(double k, t_vec3 self);
t_vec3	vec3_div(t_vec3 self, double k);
double	vec3_length(t_vec3 self);
t_vec3	vec3_negate(t_vec3 self);
double	vec3_dot(t_vec3 self, t_vec3 other);
t_vec3	vec3_cross(t_vec3 self, t_vec3 other);
t_vec3	vec3_normalize(t_vec3 self);

bool vec3_eq(t_vec3 self, t_vec3 other);
bool	vec3_is_unit(t_vec3 self);
bool	vec3_is_bogus(t_vec3 self);

t_vec3	vec3_bogus(void);

#endif // T_VEC3_H
