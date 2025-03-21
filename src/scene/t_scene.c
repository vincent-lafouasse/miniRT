#include "t_scene.h"

#include "./objects/t_hittable_array.h"

t_scene scene_new(t_ambient_light ambient_light, t_point_light point_light, t_hittable_array *objects)
{
	return ((t_scene){.ambient_light = ambient_light, .point_light = point_light, .objects = objects});
}

void scene_destroy(t_scene *scene)
{
	hittable_array_destroy(&scene->objects);
}
