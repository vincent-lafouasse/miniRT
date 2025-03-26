#ifndef T_MATERIAL_H
#define T_MATERIAL_H

struct s_material {
    double ambient;
    double diffuse;
    double specular;
    double alpha;
};
typedef struct s_material t_material;

t_material material_default(void);
t_material material_matte(void);
t_material material_shiny(void);

#endif
