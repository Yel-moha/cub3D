/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/04/26 16:47:59 by yel-moha         ###   ########.fr       */
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

//debug
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// void	player_init(t_game *game)
// {

// }

void	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(
		game->img.img_ptr,
		&game->img.bpp,
		&game->img.line_len,
		&game->img.endian
	);
}

// void	texture_loading()
// {
// 	while()
// 	{
// 		mlx_xpm_file_to_image();
// 		mlx_get_data_addr();
// 	}
// }

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

		// DEBUG VISIVO DEL RAGGIO NELLA MAPPA
		put_pixel(&game->img, ray->map_x * 4, ray->map_y * 4, 0x00FF0000);
		
		if (ray->map_y < 0 || ray->map_y >= game->map.height ||
				ray->map_x < 0 || ray->map_x >= game->map.width)
			break ;
		if(game->scene->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

int	render_frame(void *param)
{
	t_game	*game;
	int		x;

	game = (t_game *)param;

	// debug - pulizia schermo (nero)
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
		((int *)game->img.addr)[i] = 0x000000;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, game->rays, x);
		perform_dda(game, game->rays);
		//compute_distance(game, game->rays[x]);
		//draw_column(game, game->rays[x], x);
		x++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return(0);
}

void	engine_init(t_game *game)
{
	game->map = game->scene->map; // Aggiunto da youssef
	
	game->mlx = mlx_init();
	if (!game->mlx)
		return ; // TO-DO clean_exit();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return ; // TO-DO clean_exit();

	init_image(game);
	//player_init(game);
	//texture_loading(game);

	game->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (!game->rays)
		return ; // TO-DO clean_exit();

	mlx_loop_hook(game->mlx, render_frame, game);

	
	/*Questo aggiunto da youssef*/
	//Gestione della chiusura della finestra usando ESC e X
	mlx_key_hook(game->win, key_hook, (void *)game);
	mlx_hook(game->win, 17, 0, close_window, (void *)game);
	/*Fine parte aggiunta da youssef*/

	
	mlx_loop(game->mlx);

	// render_frame è dove fai:
	// raycasting
	// disegno

	// raycasting();
	// dda(game);
	// perp_wall_dist();
}
