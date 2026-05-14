/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 22:24:43 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/14 22:32:13 by anacotti         ###   ########.fr       */
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

void	clean_exit(t_game *game)
{
	if (!game)
		exit(0);
	if (game->rays)
	{
		free(game->rays);
		game->rays = NULL;
	}
	if (game->mini_map)
	{
		free(game->mini_map);
		game->mini_map = NULL;
	}
	destroy_textures(game);
	if (game->img.img_ptr)
	{
		mlx_destroy_image(game->mlx, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(0);
}
