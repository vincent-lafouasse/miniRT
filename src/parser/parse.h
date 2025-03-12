#ifndef PARSE_H
# define PARSE_H

# include "error/t_error.h"
# include "camera/t_camera.h"
# include "scene/t_scene.h"

t_error	parse(char *input, t_camera *cam_out, t_scene *scene_out);

#endif // PARSE_H
