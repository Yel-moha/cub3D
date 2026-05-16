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

void	cleanup_and_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	destroy_textures(game);
	if (game->mini_map)
	{
		free(game->mini_map);
		game->mini_map = NULL;
	}
	if (game->img.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->rays);
	free_scene(game->scene);
	exit(code);
}
