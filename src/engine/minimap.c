/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:02 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/14 21:55:26 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	get_player_pos(t_game *game, int map_w_px, int tile)
{
	t_point	p;

	p.x = PADDING + game->mini_map->off_width
		+ (map_w_px - (int)(game->scene->player->pos_x * tile));
	p.y = PADDING + game->mini_map->off_height
		+ (int)(game->scene->player->pos_y * tile);
	return (p);
}

static t_point	get_ray_target(t_game *game, int i, int map_w_px, int tile)
{
	t_point	p;

	p.x = PADDING + game->mini_map->off_width
		+ (map_w_px - ((game->rays[i].map_x * tile) + tile / 2));
	p.y = PADDING + game->mini_map->off_height
		+ game->rays[i].map_y * tile + tile / 2;
	return (p);
}

void	draw_rays_on_minimap(t_game *game)
{
	int		i;
	int		tile;
	int		map_w_px;
	t_point	player;
	t_point	target;

	if (!game || !game->mini_map || !game->scene)
		return ;
	tile = game->mini_map->tile;
	map_w_px = game->scene->map.width * tile;
	player = get_player_pos(game, map_w_px, tile);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		target = get_ray_target(game, i, map_w_px, tile);
		draw_line(&game->img, player, target, 0x00FF0000);
		i++;
	}
}
