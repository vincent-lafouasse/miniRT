/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_element.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:25:59 by jamar             #+#    #+#             */
/*   Updated: 2025/04/01 19:26:12 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ELEMENT_H
# define T_ELEMENT_H

# include "math/t_vec3/t_vec3.h"

# include <stdint.h>

# define TAG_AMBIENT_LIGHT "A"
# define TAG_CAMERA "C"
# define TAG_LIGHT "L"
# define TAG_SPHERE "sp"
# define TAG_PLANE "pl"
# define TAG_CYLINDER "cy"
# define TAG_TRIANGLE "tr"

typedef enum e_element_kind				t_element_kind;
enum									e_element_kind
{
	ELEM_AMBIENT_LIGHT,
	ELEM_CAMERA,
	ELEM_LIGHT,
	ELEM_SPHERE_PRIMITIVE,
	ELEM_PLANE_PRIMITIVE,
	ELEM_CYLINDER_PRIMITIVE,
	ELEM_TRIANGLE_PRIMITIVE,
};

typedef struct s_ambient_light_element	t_ambient_light_element;
struct									s_ambient_light_element
{
	double								lighting_ratio;
	uint8_t								color[3];
};

typedef struct s_camera_element			t_camera_element;
struct									s_camera_element
{
	t_vec3								coordinates;
	t_vec3								orientation;
	uint8_t								fov;
};

typedef struct s_light_element			t_light_element;
struct									s_light_element
{
	t_vec3								coordinates;
	double								brightness_ratio;
	uint8_t								color[3];
};

typedef struct s_sphere_element			t_sphere_element;
struct									s_sphere_element
{
	t_vec3								center;
	double								diameter;
	uint8_t								color[3];
};

typedef struct s_plane_element			t_plane_element;
struct									s_plane_element
{
	t_point3							point;
	t_vec3								normal;
	uint8_t								color[3];
};

typedef struct s_cylinder_element		t_cylinder_element;
struct									s_cylinder_element
{
	t_point3							point;
	t_vec3								axis;
	double								diameter;
	double								height;
	uint8_t								color[3];
};

typedef struct s_triangle_element		t_triangle_element;
struct									s_triangle_element
{
	t_point3							a;
	t_point3							b;
	t_point3							c;
	uint8_t								color[3];
};

typedef struct s_element				t_element;
struct									s_element
{
	t_element_kind						kind;
	union
	{
		t_ambient_light_element			ambient;
		t_camera_element				camera;
		t_light_element					light;
		t_sphere_element				sphere;
		t_plane_element					plane;
		t_cylinder_element				cylinder;
		t_triangle_element				triangle;
	};
};

#endif // T_ELEMENT_H
