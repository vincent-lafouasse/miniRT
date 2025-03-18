#ifndef T_SCENE_H
# define T_SCENE_H

#include "./lights/t_ambient_light.h"
#include "./lights/t_point_light.h"
#include "./objects/t_hittable_array.h"

struct s_scene {
	t_ambient_light		ambient_light;
	t_point_light		point_light;
	t_hittable_array	*objects;
};
typedef struct s_scene	t_scene;

t_scene scene_new(t_ambient_light ambient_light, t_point_light point_light, t_hittable_array *objects);

#endif // T_SCENE_H
