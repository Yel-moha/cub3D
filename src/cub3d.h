/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/02 22:20:41 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_tex_paths {
    char *no;
    char *so;
    char *we;
    char *ea;
} t_tex_paths;


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
} t_scene;


/***** structs x engine *****/

typedef struct s_ray
{
    float   ray_angle;
    float   wall_hit_x;
    float   wall_hit_y;
    float   distance;
    bool    is_ray_facing_up;
    bool    is_ray_facing_down;
    bool    is_ray_facing_left;
    bool    is_ray_facing_right;
    bool    was_hit_vertical;
}           t_ray;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_map       map;
    t_assets    asset_data;
    t_img       img;
    t_ray       rays[WINDOW_WIDTH];
    t_player    player;
}               t_game;

