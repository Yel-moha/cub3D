/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:23:45 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/02 15:01:49 by yel-moha         ###   ########.fr       */
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
	if (keycode == 65307) // ESC
        cleanup_and_exit(game, 0);
    else if (keycode == 119) // 'w'
        move_player(game, 1.0);
    else if (keycode == 115) // 's'
        move_player(game, -1.0);
    else if (keycode == 97) // 'a' strafe left
        strafe_player(game, -1.0);
    else if (keycode == 100) // 'd' strafe right
        strafe_player(game, 1.0);
    else if (keycode == 65361) // left arrow
        rotate_player(game, -0.08);
    else if (keycode == 65363) // right arrow
        rotate_player(game, 0.08);
    return (0);
}

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}