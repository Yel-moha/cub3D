/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dimensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:14:21 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/09 14:49:38 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//1 - Funzione calcolo layout
t_temp_map *init_dimensions(t_scene *scene)
{
    t_temp_map *map;
    int        tile_x;
    int        tile_y;

    map = malloc(sizeof(t_temp_map));
    if (!map)
        return (NULL);
    map->height =  MINI_WIN_HEIGHT;
    map->width =  MINI_WIN_WIDTH ;
    map->rows = scene->map.height;
    map->cols = scene->map.width;
    tile_x = map->width / map->cols;
    tile_y = map->height / map->rows;
    map->tile = (int)fmin((double)tile_x, (double)tile_y);
    if (map->tile < 1)
        map->tile = 1;
    map->map_width = map->cols * map->tile;
    map->map_height = map->rows * map->tile;
    map->off_width = (map->width - map->map_width) / 2; //offset
    map->off_height = (map->height - map->map_height) / 2;
    map->mlx = NULL;
    map->win = NULL;
    map->img.img_ptr = NULL;
    map->img.addr = NULL;
    return (map);
}

//2 - Funzione Calcolo griglia
void draw_grill(t_game *game)
{   
    if (game->mini_map)
    {
        free(game->mini_map);
        game->mini_map = NULL;
    }
    game->mini_map = init_dimensions(game->scene);
    if (!game->mini_map)
        return ;
    init_graphics(game);
}