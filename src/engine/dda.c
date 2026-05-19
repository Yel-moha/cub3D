/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:31:39 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/19 22:21:20 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dda_steps(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
}

static int	dda_step(t_game *game, t_ray *ray)
{
	char	cell;

	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->side_dist_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->was_hit_vertical = 0;
	}
	if (ray->map_y < 0 || ray->map_y >= game->scene->map.height
		|| ray->map_x < 0 || ray->map_x >= game->scene->map.width)
		return (1);
	cell = game->scene->map.grid[ray->map_y][ray->map_x];
	if (cell == '1'
		|| (cell == 'D' && !game->door_open[ray->map_y][ray->map_x]))
		return (1);
	return (0);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	init_dda_steps(ray);
	while (!dda_step(game, ray))
		;
}
