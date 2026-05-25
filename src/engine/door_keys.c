/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:30:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/25 20:25:40 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_door_search(t_door_search *search)
{
	search->x = 0;
	search->y = 0;
	search->found_x = -1;
	search->found_y = -1;
	search->min_dist = 2.0;
}

static void	update_door_search(t_game *game, t_door_search *search)
{
	double	dx;
	double	dy;
	double	dist;

	dx = game->scene->player->pos_x - (search->x + 0.5);
	dy = game->scene->player->pos_y - (search->y + 0.5);
	dist = sqrt(dx * dx + dy * dy);
	if (dist < search->min_dist)
	{
		search->min_dist = dist;
		search->found_x = search->x;
		search->found_y = search->y;
	}
}

static void	apply_door_toggle(t_game *game, t_door_search *search)
{
	char	cell;

	if (search->found_x == -1 || search->found_y == -1)
		return ;
	cell = game->scene->map.grid[search->found_y][search->found_x];
	if (cell == 'O')
	{
		game->scene->map.grid[search->found_y][search->found_x] = 'D';
		game->door_open[search->found_y][search->found_x] = 0;
		return ;
	}
	game->door_open[search->found_y][search->found_x]
		= !game->door_open[search->found_y][search->found_x];
}

void	toggle_nearest_door(t_game *game)
{
	t_door_search	search;

	init_door_search(&search);
	while (search.y < game->scene->map.height)
	{
		search.x = 0;
		while (search.x < game->scene->map.width)
		{
			if (game->scene->map.grid[search.y][search.x] == 'D'
				|| game->scene->map.grid[search.y][search.x] == 'O')
				update_door_search(game, &search);
			search.x++;
		}
		search.y++;
	}
	apply_door_toggle(game, &search);
}
