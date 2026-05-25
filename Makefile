NAME		= cub3d

SRCS		=	src/parsing/read_maps.c \
				src/main.c \
				src/parsing/errors.c \
				src/parsing/errors_utils.c \
				src/parsing/debug_prints.c \
				src/parsing/validations.c \
				src/parsing/free_utils.c \
				src/parsing/parse_line.c \
				src/parsing/map_grid.c \
				src/parsing/grid.c \
				src/parsing/parse_colors.c \
				src/parsing/parse_textures.c \
				src/parsing/textures_fill.c \
				src/parsing/grid_errors.c \
				src/parsing/grid_validation.c \
				src/parsing/grid_validation_utils.c \
				src/parsing/grid_validation_rows.c \
				src/parsing/read_maps_helpers.c \
				src/engine/engine.c \
				src/engine/dda.c \
				src/engine/floor_ceiling_tex.c \
				src/engine/init_graphics_1.c \
				src/engine/init_graphics_1_draw.c \
				src/engine/init_graphics_1_lines.c \
				src/engine/minimap.c \
				src/engine/player_init.c \
				src/engine/player_movment.c \
				src/engine/door_keys.c \
				src/engine/raycasting.c \
				src/engine/render_colums.c \
				src/engine/render_frame.c \
				src/engine/render_utils.c \
				src/engine/textures_access.c \
				src/engine/clean_exit.c \
				src/engine/handle_keys.c \
				src/engine/init_dimensions.c \
				src/engine/init_graphics.c \
				src/engine/sprites.c \
				src/engine/sprites_utils.c \
				src/engine/sprites_render.c \
				src/engine/sprites_draw.c \

OBJS		= $(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Wno-error=incompatible-pointer-types -g -Isrc

# Build-time debug flags
# -DRAY_DEBUG: when defined, enables drawing of DDA steps (ray traversal)
# on the main image for visual debugging of ray paths. To disable, remove
# -DRAY_DEBUG from the `DEBUG_FLAGS` below or compile without it.
DEBUG_FLAGS	= -DRAY_DEBUG

# Append debug flags to CFLAGS so the project compiles with ray debug enabled
CFLAGS		+= $(DEBUG_FLAGS)

# libft
LIBFT_DIR	= src/libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# minilibx
MLX_DIR		= src/minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS)  $(LIBFT_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	echo "INC=/usr/include" > $(MLX_DIR)/Makefile.gen
	cat $(MLX_DIR)/Makefile.mk | grep -v %%%% >> $(MLX_DIR)/Makefile.gen
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen CC="gcc -std=gnu17" all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re