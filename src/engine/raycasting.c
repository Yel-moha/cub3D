/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:15 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/19 21:46:32 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;
	t_scene	*scene;

	scene = game->scene;
	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir_x = scene->player->dir_x + scene->player->plane_x * camera_x;
	ray->dir_y = scene->player->dir_y + scene->player->plane_y * camera_x;
	ray->pos_x = scene->player->pos_x;
	ray->pos_y = scene->player->pos_y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	compute_distance(t_game *game, t_ray *ray)
{
	(void)game;
	if (!ray)
		return ;
	if (ray->was_hit_vertical)
		ray->perp_dist = ray->side_dist_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_y;
	if (ray->perp_dist <= 0)
		ray->perp_dist = 1e-6;
}
