/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/23 19:47:25 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
// Da cancellare poi
#include <stdio.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// gestita nel parsing usando la preziosissima funziona ft_split da libft
typedef struct s_tex_paths {
    char *no;
    char *so;
    char *we;
    char *ea;
} t_tex_paths;


// typedef struct s_texture
// {
//     void *img;
//     char *addr;
//     int   width;
//     int   height;
// } t_texture;

typedef struct s_rgb {
    int r;
    int g;
    int b;
    int value; /* opzionale: (r << 16) | (g << 8) | b */
} t_rgb;

typedef struct s_map {
    char **grid;
    int   width;
    int   height;
    int   letta;
} t_map;

typedef struct s_player {
    int    tile_x;
    int    tile_y;
    double pos_x;
    double pos_y;
    char   spawn;   /* N/S/E/W */
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_scene {
    t_tex_paths textures;
    t_rgb       floor;
    t_rgb       ceiling;
    t_map       map;
    t_player    player;
    int         counter;  //usata per contare le linee di percorsi e colori prima della mappa
    char        *flag;
    int         pos; //usata per quantificare N,E,W,S dentro la mappa
} t_scene;


/***** structs x engine *****/

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

	double  perp_dist;
	
	int was_hit_vertical;
}           t_ray;

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
    void        *mlx;
    void        *win;
    t_scene     *scene;
    t_map       map;
    t_img       img;
    t_ray       *rays; //fixed
    t_player    player;
}               t_game;


/********************************************************/


// Estratto direttamente del progetto get_next_line al fine di leggere il file della mappa
char	*get_next_line(int fd);
///////////////////////////////////////////////////////////////////////////////////////////


// Validations funcions
void    fill_direction(char **line, t_scene *scene);
void    fill_colors(char **line, t_scene *scene, char f_or_c);
void    fill_map(char *line, t_scene *scene);
int     check_colors_value(char **rgb_split, char **split);
void    update_flags(t_scene *scene, char *flag);


// Errors functions
int    read_map_errors(char *line);

// Debug and Prints
void    print_split(char **split);
void    print_text_paths(t_scene scene);
void	print_colors(t_scene scene);
void    print_player(t_scene scene);
void    print_map(t_scene scene);
void    print_grid(t_scene scene);

// free functions
void	free_split(char **split);
void    free_paths(t_tex_paths *pos_text);
void    free_colors(t_rgb *flo_ciel);
void    free_scene(t_scene *scene);

//parse line
void    parse_line(const char *map_path, t_scene *scene);




//map_grid
void    count_grid_height(char *line, t_scene *scene);
int     max_line(char *line, t_scene *scene);
void    fill_grid(t_scene *scene, int i, char *line);
void    allocate_grid(t_scene *scene);


// errors
void    double_color_path(char flag, t_scene *scene, char **split);
void    error_colors_value(char *line, char **rgb_split, t_scene *scene, char *joined);
void    error_spawn_player(char *line, t_scene *scene);
void    line_errors(char *line, int fd);
void	split_error(char **split);

// grid
void	parse_grid(t_scene *scene, int fd, char *line);
int     is_map_line(char *line);
void	fill_grid_pass(const char *map_path, t_scene *scene);

// parse colors
void    parse_colors(char *line, t_scene *scene);
void    parse_textures(char *line, t_scene *scene, int fd);

//grind errors
void check_extra_chars(t_scene *scene, char *line, char **split);

//grid validation
int	validate_borders(const char *map_path, t_scene *scene);
int	validate_line(char *line, int index, t_scene *scene);

//engine
void	engine_init(t_game *game);
int 	render_frame(void *param);
void	perform_dda(t_game *game, t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int x);

void	init_image(t_game *game);
void	player_init(t_game *game);

#endif