/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 18:14:21 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/26 19:11:51 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	init_image_map(t_temp_map *map)
{
	map->img.img_ptr = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	map->img.addr = mlx_get_data_addr(
		map->img.img_ptr,
		&map->img.bpp,
		&map->img.line_len,
		&map->img.endian
	);
}

//1 - Funzione calcolo layout
t_temp_map *init_dimensions(t_scene *scene)
{
    t_temp_map *map;

    map = malloc(sizeof(t_temp_map));
    map->height = WINDOW_HEIGHT - 2 * PADDING;
    map->width = WINDOW_WIDTH - 2 * PADDING;
    map->cols = scene->map.height;
    map->rows = scene->map.width;
    //Da verificare se l'arrotondamento lo dobbiamo fare di persona oopure 
    //se essendo map->tile di tipo int allora e automatico
    //tile della mappa indica la dimesione della cella o piastrella singola
    map->tile = fmin((WINDOW_WIDTH/map->cols),(WINDOW_HEIGHT/map->rows));
    //le nuove misure che qui otteniamo sono le nuove unita di misura in 
    //celle invece che in pixel
    map->map_width = map->cols * map->tile;
    map->map_height = map->width * map->tile;

    //Qui definiamo l'offset per la width e poi per la heigt
    map->off_width = (map->width - map->map_width) / 2;
    map->off_height = (map->width - map->map_height) / 2;
    return (map);
}

//2 - Funzione Calcolo griglia
void draw_grill(t_scene *scene)
{
    t_temp_map *map;
    
    map = init_dimensions(scene);
    map->mlx = mlx_init();
    if (!map->mlx)
        return;//Da implementare una funzione di cleanup  and exit
    map->win = mlx_new_window(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!map->win)
		return ; //Da implementare una funzione di cleanup  and exit
	init_image_map(map);
    mlx_key_hook(map->win, key_hook, (void *)map);
	mlx_hook(map->win, 17, 0, close_window, (void *)map);
    mlx_loop(map->mlx);
}