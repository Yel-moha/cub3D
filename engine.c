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

}

void	raycasting()
{
	int	x;

	x = 0;
	while(x < WINDOW_WIDTH)
	{
		camera_x = 2 * x / width - 1;
		ray_dir = dir + plane * camera_x
		x++;
	}
}

void	perform_dda(t_game *game)
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	
//which box of the map we're in
	map_x = (int)game->scene->player.pos_x;
	map_y = (int)game->scene->player.pos_y;
	
//length of ray from one x or y-side to next x or y-side
	delta_x = fabs(1 / ray_dir_x);
	delta_y = fabs(1 / ray_dir_y);

	if (ray->dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player.pos_x - map_x) * delta_x; //go left
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player.pos_x) * delta_x; //go right
	}

	if (ray->dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player.pos_y - map_y) * delta_y; //go left
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player.pos_y) * delta_y; //go right
	}
	
//length of ray from current position to next x or y-side
	side_dist_x = ;
	side_dist_y = ;

	while()
	{
		if(side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			ray->was_hit_vertical = 1; //avanzo nella direzione minore
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			ray->was_hit_vertical = 0;
		}

		if(game->scene->map.grid[map_y][map_x] == '1')
			break ;
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