/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_material.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:14:09 by poss              #+#    #+#             */
/*   Updated: 2025/03/30 01:14:18 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MATERIAL_H
# define T_MATERIAL_H

struct	s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	alpha;
};
typedef struct s_material	t_material;

t_material	material_default(void);
t_material	material_matte(void);
t_material	material_shiny(void);

#endif
