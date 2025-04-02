NAME = miniRT

### definitions

CC        = cc
CFLAGS    += -Wall -Wextra -Werror
ifdef DEBUG_MODE
	DEBUG_FLAGS = -g3
	OPTIMIZATION_FLAGS =
else
	OPTIMIZATION_FLAGS = -O3 -flto
endif
CFLAGS += $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS)

CPPFLAGS  = -Isrc -MMD -MP
LDLIBS = -lm
LDFLAGS = $(OPTIMIZATION_FLAGS)

SRCS  = src/main.c

SRCS += src/camera/camera_new.c
SRCS += src/camera/cast_rays.c
SRCS += src/camera/render_scene.c

SRCS += src/parser/element/t_element_list/constructor.c
SRCS += src/parser/element/t_element_list/destructors.c
SRCS += src/parser/element/t_element_list/operations.c
SRCS += src/parser/element/t_element_list/properties.c
SRCS += src/parser/element/element_property_parse.c
SRCS += src/parser/element/hittable_from_primitive.c
SRCS += src/parser/element/match_element.c
SRCS += src/parser/element/match_primitive.c
SRCS += src/parser/element/match_properties.c
SRCS += src/parser/element/t_partitioned_elements.c
SRCS += src/parser/double_parse.c
SRCS += src/parser/ends_in_dot_rt.c
SRCS += src/parser/gather_objects_lights.c
SRCS += src/parser/parse.c
SRCS += src/parser/u8_parse.c

SRCS += src/read/t_string/alloc.c
SRCS += src/read/t_string/c_string.c
SRCS += src/read/t_string/constructor.c
SRCS += src/read/t_string/destructor.c
SRCS += src/read/t_string/insert.c
SRCS += src/read/t_string/realloc.c
SRCS += src/read/read_file.c

SRCS += src/ray/t_ray.c

SRCS += src/scene/lights/t_point_light_array/point_light_array_destroy.c
SRCS += src/scene/lights/t_point_light_array/point_light_array_new.c
SRCS += src/scene/lights/t_point_light_array/point_light_array_push.c
SRCS += src/scene/lights/light_constructor.c
SRCS += src/scene/objects/cylinder/cylinder_cap_hit.c
SRCS += src/scene/objects/cylinder/cylinder_hit.c
SRCS += src/scene/objects/cylinder/cylinder_shaft_hit.c
SRCS += src/scene/objects/cylinder/t_cylinder.c
SRCS += src/scene/objects/plane/plane_hit.c
SRCS += src/scene/objects/plane/plane_new.c
SRCS += src/scene/objects/sphere/sphere_hit.c
SRCS += src/scene/objects/sphere/t_sphere.c
SRCS += src/scene/objects/t_hittable_array/hittable_array_destroy.c
SRCS += src/scene/objects/t_hittable_array/hittable_array_hit.c
SRCS += src/scene/objects/t_hittable_array/hittable_array_new.c
SRCS += src/scene/objects/t_hittable_array/hittable_array_push.c
SRCS += src/scene/objects/triangle/triangle_hit.c
SRCS += src/scene/objects/triangle/triangle_new.c
SRCS += src/scene/objects/object_color.c
SRCS += src/scene/objects/object_hit.c
SRCS += src/scene/objects/t_hittable_constructor.c
SRCS += src/scene/shading/ambient.c
SRCS += src/scene/shading/diffuse.c
SRCS += src/scene/shading/hit_is_in_the_shadow.c
SRCS += src/scene/shading/specular.c
SRCS += src/scene/shading/t_material.c
SRCS += src/scene/ray_color.c
SRCS += src/scene/t_scene.c

SRCS += src/render/display.c
SRCS += src/render/exit_loop.c
SRCS += src/render/hooks.c
SRCS += src/render/renderer_destroy.c
SRCS += src/render/renderer_enter_loop.c
SRCS += src/render/renderer_init.c

SRCS += src/math/double/double_eq.c
SRCS += src/math/t_interval/t_interval.c
SRCS += src/math/t_rgb/rgb_convertion.c
SRCS += src/math/t_vec3/vec3_arithmetic.c
SRCS += src/math/t_vec3/vec3_bogus.c
SRCS += src/math/t_vec3/vec3_eq.c
SRCS += src/math/t_vec3/vec3_normalize.c
SRCS += src/math/t_vec3/vec3_products.c

SRCS += src/error/die.c
SRCS += src/error/error_repr.c
SRCS += src/error/log_error.c

OBJS := $(SRCS:%=build/%.o)
DEPS := $(OBJS:.o=.d)

### libraries

LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKE_DIR = $(LIBFT_DIR)
LIBFT_INCLUDE_DIR = $(LIBFT_DIR)/include

CPPFLAGS += -I$(LIBFT_INCLUDE_DIR)
LDLIBS += $(LIBFT)

MLX_DIR = ./lib/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_MAKE_DIR = $(MLX_DIR)
MLX_INCLUDE_DIR = $(MLX_DIR)

CPPFLAGS += -I$(MLX_INCLUDE_DIR)
LDLIBS += $(MLX) -lXext -lX11

### targets

.PHONY: all
all: build

.PHONY: build
build: $(NAME)

# Linking
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Compilation
build/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_MAKE_DIR)

$(MLX):
	(cd $(MLX_DIR); ./configure)
	make -C $(MLX_MAKE_DIR)

.PHONY: bonus
bonus: CFLAGS += -D BONUS_MODE
bonus: build

.PHONY: re
re: clean build

.PHONY: clean
clean:
	$(RM) -r build/src
	make clean -C $(MLX_MAKE_DIR)
	make clean -C $(LIBFT_MAKE_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX)
	make fclean -C $(LIBFT_MAKE_DIR)

.PHONY: test
test: $(LIBS)
	cmake -DCMAKE_BUILD_TYPE=DEBUG -S test -B build/test
	cmake --build build/test
	GTEST_COLOR=1 ctest --test-dir build/test $(CTEST_OPT)

.PHONY: vtest
ifdef TEST_WITH_MEMCHECK
vtest: CTEST_OPT += -T memcheck
endif
vtest: CTEST_OPT += -V
vtest: test

# LSP stuff, don't worry about it
.PHONY: update
update: clean
	mkdir -p build
	bear --output build/compile_commands.json -- make build
	# merge with CMake maintained data
	jq -s add build/compile_commands.json build/test/compile_commands.json >build/tmp
	mv build/tmp build/compile_commands.json

.PHONY: run
run: build
	exec ./$(NAME)

# aliases
.PHONY: b c u r t vt
b: build
c: clean
u: update
r: run
t: test
vt: vtest

-include $(DEPS)
