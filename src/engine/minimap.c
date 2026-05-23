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

static t_point	get_player_pos(t_game *game, int tile)
{
	t_point	p;

	p.x = PADDING + game->mini_map->off_width
		+ (int)(game->scene->player->pos_x * tile);
	p.y = PADDING + game->mini_map->off_height
		+ (int)(game->scene->player->pos_y * tile);
	return (p);
}

static t_point	get_ray_target(t_game *game, int i, int tile)
{
	t_point	p;
	double	hit_x;
	double	hit_y;

	hit_x = game->rays[i].pos_x + game->rays[i].dir_x
		* game->rays[i].perp_dist;
	hit_y = game->rays[i].pos_y + game->rays[i].dir_y
		* game->rays[i].perp_dist;
	p.x = PADDING + game->mini_map->off_width
		+ (int)(hit_x * tile);
	p.y = PADDING + game->mini_map->off_height
		+ (int)(hit_y * tile);
	return (p);
}

void	draw_rays_on_minimap(t_game *game)
{
	int		i;
	int		tile;
	t_point	player;
	t_point	target;

	if (!game || !game->mini_map || !game->scene)
		return ;
	tile = game->mini_map->tile;
	player = get_player_pos(game, tile);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		target = get_ray_target(game, i, tile);
		draw_line(&game->img, player, target, 0x00FF0000);
		i++;
	}
}
