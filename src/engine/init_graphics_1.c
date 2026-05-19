/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:27:09 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/19 22:10:10 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_minimap(t_temp_map *map)
{
	if (!map)
		return (0);
	if (map->mlx)
		mlx_loop_end(map->mlx);
	if (map->img.img_ptr && map->mlx)
		mlx_destroy_image(map->mlx, map->img.img_ptr);
	if (map->win && map->mlx)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free(map);
	return (0);
}

static int	key_hook_minimap(int keycode, t_temp_map *map)
{
	if (keycode == XK_Escape)
		return (close_minimap(map));
	return (0);
}

static int	init_image_map(t_temp_map *map)
{
	map->img.img_ptr = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!map->img.img_ptr)
		return (0);
	map->img.addr = mlx_get_data_addr(map->img.img_ptr,
			&map->img.bpp, &map->img.line_len, &map->img.endian);
	return (1);
}

static int	init_minimap_window(t_game *game)
{
	game->mini_map->mlx = mlx_init();
	if (!game->mini_map->mlx)
		return (0);
	game->mini_map->win = mlx_new_window(game->mini_map->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "mini_map");
	if (!game->mini_map->win || !init_image_map(game->mini_map))
		return (close_minimap(game->mini_map));
	mlx_key_hook(game->mini_map->win, key_hook_minimap, game->mini_map);
	mlx_hook(game->mini_map->win, 17, 0, close_minimap, game->mini_map);
	return (1);
}

void	init_graphics_one(t_game *game)
{
	if (!game || !game->mini_map || !game->scene)
		return ;
	if (!init_minimap_window(game))
		return ;
	render_minimap(game);
	mlx_loop(game->mini_map->mlx);
}
