/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:38:23 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/03 14:49:08 by yel-moha         ###   ########.fr       */
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

# define WINDOW_WIDTH 1400
# define WINDOW_HEIGHT 800



# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif


typedef struct s_temp_map				t_temp_map;
// gestita nel parsing usando la preziosissima funziona ft_split da libft
typedef struct s_tex_paths {
    char *no;
    char *so;
    char *we;
    char *ea;
} t_tex_paths;

// mi pare intuile, possiamo eliminarla
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
    t_rgb       floor; //verifichiamo la corretta gestione
    t_rgb       ceiling; //verifichiamo la corretta gestione
    t_map       map;
    t_player    *player;
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
    t_temp_map  *mini_map; // aggiunta per la stampa della minimappa
    //t_map       map; //prendiomola direttamente da scene semmai -> sì, sono d'accordo
    t_img       img;
    t_ray       *rays; //fixed
    //t_player    *player; direi di rimuovere, già presente in struct scene
    
    /* support full X11 keysyms (up to 65535) */
    int         keys[65536];
    double      last_time; /* seconds since epoch of last frame */
    
    /* textures for walls: 0=NO,1=SO,2=WE,3=EA */
    t_img       tex[4];
    int         tex_w[4];
    int         tex_h[4];
}               t_game;


/********************************************************/


// Estratto direttamente del progetto get_next_line al fine di leggere il file della mappa
char	*get_next_line(int fd);
///////////////////////////////////////////////////////////////////////////////////////////


// Validations funcions
void    fill_direction(char **line, t_scene *scene);
void    fill_direction_fixed(char **line, t_scene *scene, int path_index);
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
void    error_extra_line_map(char *line, t_scene *scene);

// textures_accec.c
int textures_exist(t_scene *scene);
void textures_error_path(t_scene *scene);

// grid
void	parse_grid(t_scene *scene, int fd, char *line);
int     is_blank_line(char *line);
int     is_map_line(char *line);
void	fill_grid_pass(const char *map_path, t_scene *scene);

// parse colors
void    parse_colors(char *line, t_scene *scene);
void    parse_textures(char *line, t_scene *scene, int fd);

//grind errors
void    check_extra_chars_textures(t_scene *scene, char *line, char **split);
void    nl_grid_error(char *line);

//grid validation
int	validate_borders(const char *map_path, t_scene *scene);
int	validate_line(char *line, int index, t_scene *scene);

//engine
void	engine_init(t_game *game);
int 	render_frame(void *param);
void	perform_dda(t_game *game, t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int x);
/***************Youssef********************* */
void	compute_distance(t_game *game, t_ray *ray);
void	draw_column(t_game *game, t_ray *ray, int x);
void	player_init(t_game *game);
void	draw_rays_on_minimap(t_game *game);
void    fill_player_ew(char c, t_game *game,  int row, int col);
void    fill_player_ns(char c, t_game *game, int row, int col);
/*********************************************** */
void	init_image(t_game *game);
void	cleanup_and_exit(t_game *game, int code);
void	put_pixel(t_img *img, int x, int y, int color);
int		load_texture(t_game *game, int i, char *path);
int		load_textures(t_game *game);
void	draw_floor_ceiling(t_game *game);

//player_movement






//engine/player_movment.c
void	move_player(t_game *game, double forward);
void	strafe_player(t_game *game, double right);
void	rotate_player(t_game *game, double angle);

//engine/testes.c
int	key_hook(int keycode, t_game *game);
int	close_window(t_game *game);
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
void	handle_keys(t_game *game, double dt);







# define MINI_WIN_WIDTH (WINDOW_WIDTH/5)
# define MINI_WIN_HEIGHT (WINDOW_HEIGHT/4)
# define PADDING 10 // spazio di sicurezza tra la mappa e il bordo della finestra
//Il padding sopra definito serve per 
//1 - Evitare che muri e player tocchino il bosrdo dello schermo
//2 - Rendere piu leggibile la minimappa
//3 - Lascia spazio per debug e overlay (testo, valori, ecc)
/*
    Esempio:
    finestra 1280x720
    padding 20
    area usabile
        larghezza: 1280 - 40
        altezza;   720 - 40

    Calcolo Aree
        +Area interna: // Continuo all'interno del file tests.c
*/
    
//STRUTTURA TEMPORANEA PER YOUSSEF
typedef struct s_temp_map {
    int height;
    int width;
    int cols;
    int rows;
    int tile;
    int map_width;
    int map_height;
    int off_width;
    int off_height;
    
    //per l'uso di minilibx
    void        *mlx;
    void        *win;
    t_img       img;
    
} t_temp_map;






//engine/dimensions
void draw_grill(t_game *game);
t_temp_map *init_dimensions(t_scene *scene);

//init_graphics
void	init_graphics(t_game *game);

#endif