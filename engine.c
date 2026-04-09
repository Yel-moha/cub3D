/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/04/02 21:31:38 by anacotti         ###   ########.fr       */
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

void	raycasting()
{
	int	x;

	x = 0;
	while(x =< WINDOW_WIDTH)
	{
		camera_x = 2 * x / width - 1;
		ray_dir = dir + plane * camera_x
		x++;
	}
}

void	dda()
{
	map_x = (int)pos_x;
	map_y = (int)pos_y;

	delta_x = abs(1 / ray_dir_x);
	delta_y = abs(1 / ray_dir_y);

	if(ray_dir_x < 0)
	{
		left;
	}
	else
	{
		right;
	}

	side_dist_x = ;
	side_dist_y = ;

	while()
	{
		if(side_dist_x > side_dist_y)
		{
			//avanzi nella direzione minore
		}
		else if(side_dist_x < side_dist_y)
		{
			//avanzi nella direzione minore
		}
		side_dist_x = ;
		side_dist_y = ;
		if(game->scene->map[y][x] == '1')
			break ;
	}
}

void	engine_init()
{
	mlx_init();
	mlx_new_window();
	mlx_new_image();
	...
	player_init();
	texture_loading();

	game->rays = malloc(...)

	mlx_loop();

	raycasting();
	dda();
	perp_wall_dist();
}