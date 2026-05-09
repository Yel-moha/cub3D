/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/09 17:20:33 by anacotti         ###   ########.fr       */
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

/*Aggiunti 29/04/2026 Da youssef*/
//void	compute_distance(t_game *game, t_ray *ray)
//void	draw_column(t_game *game, t_ray *ray, int x)
//static void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
//void	draw_rays_on_minimap(t_game *game)
/******************************************************** */

// 1.init MLX
// 2.init window
// 3.init immagini
// 4.init player
// 5.load textures
// 6.allocazioni runtime
// 7.input + hooks
// 8.loop

void	engine_init(t_game *game)
{
	int	i;

	game->map = game->scene->map; // Aggiunto da youssef
	//questo è pericoloso (copia, non riferimento), conviene usare sempre game->scene->map
	
	game->mlx = mlx_init();
	if (!game->mlx)
		return ; // TO-DO clean_exit();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return ; // TO-DO clean_exit();

	init_image(game); /* Rendering buffer */
	player_init(game); /* Game state */

	if (!load_textures(game))
	{
		// warning - textures not loaded, continue with flat colors
		write(2, "Warning: textures not loaded\n", 29); 
	}

	printf("%d %d\n", game->tex_w[0], game->tex_h[0]); //debug

	game->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH); /* Rays allocation */
	if (!game->rays)
		return ; // TO-DO clean_exit();

	/* init key states and frame timer */
	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
	game->last_time = 0.0;

	/*Questo aggiunto da youssef*/
	//Gestione della chiusura della finestra usando ESC e X

	mlx_loop_hook(game->mlx, render_frame, game);

	/* Use KeyPress/KeyRelease hooks so held keys work */
	mlx_hook(game->win, 2, 1L<<0, key_press, (void *)game);
	mlx_hook(game->win, 3, 1L<<1, key_release, (void *)game);
	mlx_hook(game->win, 17, 0, close_window, (void *)game);

	////////////
	/*Fine parte aggiunta da youssef*/

	mlx_loop(game->mlx);
}
