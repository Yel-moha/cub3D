/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 21:21:24 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(
			game->img.img_ptr,
			&game->img.bpp,
			&game->img.line_len,
			&game->img.endian);
}

static void	init_door_matrix(t_game *game)
{
	int	j;

	game->door_open = ft_calloc(game->scene->map.height, sizeof(int *));
	if (!game->door_open)
		cleanup_and_exit(game, 0);
	j = 0;
	while (j < game->scene->map.height)
	{
		game->door_open[j] = ft_calloc(game->scene->map.width, sizeof(int));
		if (!game->door_open[j])
			cleanup_and_exit(game, 0);
		j++;
	}
}

static void	init_window_and_image(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		cleanup_and_exit(game, 0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		cleanup_and_exit(game, 0);
	init_image(game);
	player_init(game);
	if (!load_textures(game))
		write(2, "Warning: textures not loaded\n", 29);
}

static void	init_runtime_allocs_and_hooks(t_game *game)
{
	int	i;

	game->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (!game->rays)
		cleanup_and_exit(game, 0);
	game->z_buffer = ft_calloc(WINDOW_WIDTH, sizeof(double));
	if (!game->z_buffer)
		cleanup_and_exit(game, 0);
	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
	game->last_time = 0.0;
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, (void *)game);
	mlx_hook(game->win, 3, 1L << 1, key_release, (void *)game);
	mlx_hook(game->win, 17, 0, close_window, (void *)game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_loop(game->mlx);
}

void	engine_init(t_game *game)
{
	game->map = game->scene->map;
	init_sprites(game);
	init_door_matrix(game);
	init_window_and_image(game);
	init_runtime_allocs_and_hooks(game);
}
