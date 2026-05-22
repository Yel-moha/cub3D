/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:23:45 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/21 20:54:39 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == 65307)
		cleanup_and_exit(game, 0);
	if (keycode == 101 && !game->door_toggle_locked)
	{
		toggle_nearest_door(game);
		game->door_toggle_locked = 1;
	}
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == 101)
		game->door_toggle_locked = 0;
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
	double	scale;

	if (!game)
		return ;
	scale = dt * 30.0;
	if (scale <= 0)
		scale = 1.0;
	if (game->keys[119])
		move_player(game, 1.0 * scale);
	if (game->keys[115])
		move_player(game, -1.0 * scale);
	if (game->keys[97])
		strafe_player(game, -1.0 * scale);
	if (game->keys[100])
		strafe_player(game, 1.0 * scale);
	if (game->keys[65361])
		rotate_player(game, 0.08 * scale);
	if (game->keys[65363])
		rotate_player(game, -0.08 * scale);
}
