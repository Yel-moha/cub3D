/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:23:45 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/27 15:54:46 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_and_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
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

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		cleanup_and_exit(game, 0);
    }
	return (0);
}

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}