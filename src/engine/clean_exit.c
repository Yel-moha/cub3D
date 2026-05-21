/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 22:24:43 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/19 21:51:47 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img_ptr)
			mlx_destroy_image(game->mlx, game->tex[i].img_ptr);
		i++;
	}
}

static void	free_door_open(t_game *game)
{
	int	i;

	if (!game->door_open)
		return ;
	if (game->scene)
	{
		i = 0;
		while (i < game->scene->map.height)
		{
			if (game->door_open[i])
				free(game->door_open[i]);
			i++;
		}
	}
	free(game->door_open);
	game->door_open = NULL;
}

static void	cleanup_game(t_game *game)
{
	destroy_textures(game);
	if (game->mini_map)
		free(game->mini_map);
	if (game->img.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_door_open(game);
	free(game->rays);
	free_scene(game->scene);
}

void	cleanup_and_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	cleanup_game(game);
	exit(code);
}
