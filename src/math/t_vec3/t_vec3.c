#include "t_vec3.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 self, t_vec3 other) {
	return vec3_new(self.x + other.x, self.y + other.y, self.z + other.z);
}

t_vec3	vec3_negate(t_vec3 self) {
	return vec3_new(-self.x, -self.y, -self.z);
}

t_vec3	vec3_sub(t_vec3 self, t_vec3 other) {
	return vec3_add(self, vec3_negate(other));
}

t_vec3	vec3_mul(double k, t_vec3 self) {
	return vec3_new(k * self.x, k * self.y, k * self.z);
}

t_vec3	vec3_div(t_vec3 self, double k);

double	vec3_length(t_vec3 self);
t_vec3	vec3_dot(t_vec3 self, t_vec3 other);
t_vec3	vec3_cross(t_vec3 self, t_vec3 other);
t_vec3	vec3_normalize(t_vec3 self);

bool	vec3_is_normalized(t_vec3 self);

t_vec3	vec3_bogus(void) {
	return vec3_new(INFINITY, INFINITY, INFINITY);
}

bool	vec3_is_bogus(t_vec3 self) {

}
