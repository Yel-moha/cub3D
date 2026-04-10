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

void	dda(t_game game)
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	
//which box of the map we're in
	map_x = (int)game.scene->player.pos_x;
	map_y = (int)game.scene->player.pos_y;
	
//length of ray from one x or y-side to next x or y-side
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
	
//length of ray from current position to next x or y-side
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

void	engine_init(t_game game)
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
	dda(game);
	perp_wall_dist();
}