#include "t_material.h"

t_material material_default(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 1.0,
        .alpha = 40,
    };
}

t_material material_matte(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 0.3,
        .alpha = 20,
    };
}

t_material material_shiny(void) {
    return (t_material){
        .ambient = 0.4,
        .diffuse = 1.0,
        .specular = 5.0,
        .alpha = 200,
    };
}
