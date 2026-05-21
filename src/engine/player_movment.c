/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 14:57:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/19 21:35:47 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, double x, double y) //modificato x bonus porte
{
	char	cell;

	cell = game->scene->map.grid[(int)y][(int)x];
	if (cell == '1')
		return (1);
	if (cell == 'D' && !game->door_open[(int)y][(int)x])
		return (1);
	return (0);
}

void	move_player(t_game *game, double forward)
{
	t_player	*player;
	double		ms;
	double		nx;
	double		ny;

	player = game->scene->player;
	ms = 0.08;
	nx = player->pos_x + player->dir_x * ms * forward;
	ny = player->pos_y + player->dir_y * ms * forward;
	if (!is_wall(game, nx, player->pos_y))
		player->pos_x = nx;
	if (!is_wall(game, player->pos_x, ny))
		player->pos_y = ny;
}

void	strafe_player(t_game *game, double right)
{
	double		ms;
	double		nx;
	double		ny;
	t_player	*player;

	player = game->scene->player;
	ms = 0.10;
	nx = player->pos_x + player->plane_x * ms * right;
	ny = player->pos_y + player->plane_y * ms * right;
	if (!is_wall(game, nx, player->pos_y))
		player->pos_x = nx;
	if (!is_wall(game, player->pos_x, ny))
		player->pos_y = ny;
}

void	rotate_player(t_game *game, double angle)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = game->scene->player;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle)
		- player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle)
		+ player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle)
		+ player->plane_y * cos(angle);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		delta;
	double	sens;

	(void)y;
	center_x = WINDOW_WIDTH / 2;
	sens = 0.003;
	delta = x - center_x;
	if (delta != 0)
	{
		rotate_player(game, -delta * sens);
		mlx_mouse_move(game->mlx,
			game->win,
			center_x,
			WINDOW_HEIGHT / 2);
	}
	return (0);
}
