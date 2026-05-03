/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:23:45 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/03 14:05:55 by yel-moha         ###   ########.fr       */
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

int	key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == 65307) // ESC
		cleanup_and_exit(game, 0);
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

void	handle_keys(t_game *game, double dt)
{
	double scale;

	if (!game)
		return ;
	/* scale so that dt ~1/60 produces scale ~= 1 */
	scale = dt * 30.0; //Fatto determinante della velocita di movineto del player
	if (scale <= 0)
		scale = 1.0;
	if (game->keys[119]) // w
		move_player(game, 1.0 * scale);
	if (game->keys[115]) // s
		move_player(game, -1.0 * scale);
	if (game->keys[97]) // a
		strafe_player(game, -1.0 * scale);
	if (game->keys[100]) // d
		strafe_player(game, 1.0 * scale);
	if (game->keys[65361]) // left arrow
		rotate_player(game, 0.08 * scale);
	if (game->keys[65363]) // right arrow
		rotate_player(game, -0.08 * scale);
}