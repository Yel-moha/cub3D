/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/18 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# define WINDOW_WIDTH 1400
# define WINDOW_HEIGHT 800
# define MINI_WIN_WIDTH 280
# define MINI_WIN_HEIGHT 200
# define PADDING 10

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_temp_map	t_temp_map;

typedef struct s_tex_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_tex_paths;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	int		value;
}	t_rgb;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		letta;
}	t_map;

typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	double	pos_x;
	double	pos_y;
	char	spawn;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_scene
{
	t_tex_paths	textures;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	*player;
	int			counter;
	char		*flag;
	int			pos;
}	t_scene;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	perp_dist;
	int		was_hit_vertical;
}	t_ray;

typedef struct s_draw_col
{
	int		tex_id;
	double	wall_x;
	int		draw_start;
	int		draw_end;
	int		line_height;
}	t_draw_col;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_temp_map	*mini_map;
	t_map		map;
	t_img		img;
	t_ray		*rays;
	int			keys[65536];
	double		last_time;
	t_img		tex[4];
	int			tex_w[4];
	int			tex_h[4];
}	t_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

typedef struct s_temp_map
{
	int		height;
	int		width;
	int		cols;
	int		rows;
	int		tile;
	int		map_width;
	int		map_height;
	int		off_width;
	int		off_height;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_temp_map;

/* get_next_line */
char	*get_next_line(int fd);
char	*append_buffer(char *buffer, char *temp);
char	*read_line(int fd, char *buffer);
size_t	line_len_with_newline(char *buffer);
char	*extract_tail(char *buffer, size_t line_len);
char	*extract_line(char **buffer);

/* parsing */
void	parse_line(const char *map_path, t_scene *scene);
void	parse_textures(char *line, t_scene *scene, int fd);
void	parse_colors(char *line, t_scene *scene);
void	fill_direction(char **line, t_scene *scene);
void	fill_direction_fixed(char **line, t_scene *scene, int path_index);
void	fill_colors(char **line, t_scene *scene, char f_or_c);
int		check_colors_value(char **rgb_split, char **split);
void	update_flags(t_scene *scene, char *flag);

/* grid */
void	count_grid_height(char *line, t_scene *scene);
int		max_line(char *line, t_scene *scene);
void	fill_grid(t_scene *scene, int i, char *line);
void	allocate_grid(t_scene *scene);
void	parse_grid(t_scene *scene, int fd, char *line);
int		is_blank_line(char *line);
int		is_map_line(char *line);
void	fill_grid_pass(const char *map_path, t_scene *scene);

/* validation */
int		validate_borders(const char *map_path, t_scene *scene);
int		validate_line(char *line, int index, t_scene *scene);
int		line_len_no_nl(char *line);
int		middle_row_is_closed(char **rows, int h, int i);
void	free_rows(char **rows, int count);
int		load_map_rows(const char *map_path, t_scene *scene, char **rows);

/* errors */
void	double_color_path(char flag, t_scene *scene, char **split);
void	error_colors_value(char *line, char **rgb_split, t_scene *scene,
			char *joined);
void	error_spawn_player(char *line, t_scene *scene);
int		is_config_id(char *id);
void	line_errors(char *line, int fd);
void	split_error(char **split);
void	error_extra_line_map(char *line, t_scene *scene);
int		textures_exist(t_scene *scene);
void	textures_error_path(t_scene *scene);
void	check_extra_chars_textures(t_scene *scene, char *line, char **split);
void	nl_grid_error(char *line, t_scene *scene);

/* memory */
void	free_split(char **split);
void	free_paths(t_tex_paths *pos_text);
void	free_scene(t_scene *scene);

/* debug */
void	print_split(char **split);
void	print_text_paths(t_scene scene);
void	print_colors(t_scene scene);
void	print_player(t_scene scene);
void	print_map(t_scene scene);
void	print_grid(t_scene scene);

/* engine */
void	engine_init(t_game *game);
void	init_graphics(t_game *game);
void	init_graphics_one(t_game *game);
void	init_image(t_game *game);
int		render_frame(void *param);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	compute_distance(t_game *game, t_ray *ray);
void	draw_column(t_game *game, t_ray *ray, int x);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point p0, t_point p1, int color);
int		load_texture(t_game *game, int i, char *path);
int		load_textures(t_game *game);
void	draw_floor_ceiling(t_game *game);

/* minimap */
void	draw_rays_on_minimap(t_game *game);
void	draw_grill(t_game *game);
t_temp_map	*init_dimensions(t_scene *scene);

/* player */
void	player_init(t_game *game);
void	fill_player_ew(char c, t_game *game, int row, int col);
void	fill_player_ns(char c, t_game *game, int row, int col);
void	move_player(t_game *game, double forward);
void	strafe_player(t_game *game, double right);
void	rotate_player(t_game *game, double angle);

/* input / cleanup */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);
int		key_release(int keycode, t_game *game);
void	handle_keys(t_game *game, double dt);
void	destroy_textures(t_game *game);
void	cleanup_and_exit(t_game *game, int code);

#endif
