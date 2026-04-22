/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/10 18:34:07 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "minilibx-linux/mlx.h"

// typedef struct s_tex_paths {
// 	char *no;
// 	char *so;
// 	char *we;
// 	char *ea;
// } t_tex_paths;

typedef struct s_texture
{
    void *img;
    char *addr;
    int   width;
    int   height;
} t_texture;

typedef struct s_assets
{
    t_texture no;
    t_texture so;
    t_texture we;
    t_texture ea;
} t_assets;

typedef struct s_rgb
{
	int r;
    int g;
    int b;
    // int value; /* opzionale: (r << 16) | (g << 8) | b */
} t_rgb;

typedef struct s_map
{
    char **grid;
    int   width;
    int   height;
} t_map;

typedef struct s_player
{
    // int    tile_x;
    // int    tile_y;
    double pos_x;
    double pos_y;
    // char   spawn;   /* N/S/E/W */
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_scene
{
	t_texture 	textures;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
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
    // t_map       map;
    t_assets    asset_data;
    t_img       img;
    t_ray       *rays[WINDOW_WIDTH];
    // t_player    player;
}               t_game;

#endif