/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/04/10 18:39:26 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
✔ player + direzione
✔ raycasting senza texture (muri colorati)
✔ DDA stabile
✔ correzione distanza
✔ rendering colonne
✔ texture
✔ movimento player
✔ collisioni
*/

void	player_init()
{

}

void	texture_loading()
{
	while()
	{
		mlx_xpm_file_to_image();
		mlx_get_data_addr();
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;
	t_scene *scene;

	scene = game->scene;
	//trasformare x in spazio camera
	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	//trasformare x in spazio camera
	ray->dir_x = scene->player.dir_x + scene->player.plane_x * camera_x;
	ray->dir_y = scene->player.dir_y + scene->player.plane_y * camera_x;
	//direzione del raggio
	ray->pos_x = scene->player.pos_x;
	ray->pos_y = scene->player.pos_y;
	//posizione del raggio
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	//delta distance
	if (ray->dir_x == 0) //per evitare crash
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_x; //go left
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x; //go right
	}

	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_y; //go left
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y; //go right
	}
	while(hit == 0)
	{
		if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->was_hit_vertical = 1; //avanzo nella direzione minore
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->was_hit_vertical = 0;
		}
		if (ray->map_y < 0 || ray->map_y >= map_height ||
				ray->map_x < 0 || ray->map_x >= map_width)
			break ;
		if(game->scene->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, &game->rays[x], x);
		perform_dda(game, &game->rays[x]);
		compute_distance(game, &game->rays[x]);
		draw_column(game, &game->rays[x], x);
		x++;
	}

	mlx_put_image_to_window(...);
}

void	engine_init(t_game game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window();

	init_image(game);
	player_init(game);
	texture_loading(game);

	game->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);

	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);

	// render_frame è dove fai:
	// raycasting
	// disegno

	// raycasting();
	// dda(game);
	// perp_wall_dist();
}