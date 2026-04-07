/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/07 17:43:30 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
// Da cancellare poi
#include <stdio.h>


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

// Estratto direttamente del progetto get_next_line al fine di leggere il file della mappa
char	*get_next_line(int fd);
///////////////////////////////////////////////////////////////////////////////////////////


// Validations funcions
void fill_direction(char **line, t_scene *scene);
void fill_colors(char **line, t_scene *scene, char f_or_c);


// Errors functions
int    read_map_errors(char *line);

// Debug and Prints
void print_split(char **split);
void print_text_paths(t_tex_paths pos_text);
void	print_colors(t_rgb colors);

// free functions
void	free_split(char **split);
void    free_paths(t_tex_paths *pos_text);
void    free_colors(t_rgb *flo_ciel);

//parse line
void parse_textures(char *map_path, t_scene *scene);
void split_errors(char **split);
void  line_errors(char *line, int fd);
void parse_colors(char **split, t_scene *scene);

#endif

