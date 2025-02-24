NAME = miniRT

### definitions

CC        = cc
CFLAGS    = -Wall -Wextra -g3
# CFLAGS   += -Werror
CPPFLAGS  = -Isrc -MMD -MP
LDLIBS = -lm
LDFLAGS =

SRCS  = $(shell find src -name '*.c')
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
	-./$(MLX_DIR)/configure
	make -C $(MLX_MAKE_DIR)

.PHONY: re
re: clean build

.PHONY: clean
clean:
	$(RM) -r build/src
	make clean -C $(MLX_MAKE_DIR)
	make clean -C $(LIBFT_MAKE_DIR)
	$(RM) Makefile.gen

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
vtest: CTEST_OPT += -V
vtest: test

# LSP stuff, don't worry about it
.PHONY: update
update: clean
	mkdir -p build
	bear --output build/compile_commands.json -- make build

# aliases
.PHONY: b c u r t vt
b: build
c: clean
u: update
r: run
t: test
vt: vtest

-include $(DEPS)
