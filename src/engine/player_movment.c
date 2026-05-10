/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 14:57:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/09 12:32:11 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	return (game->scene->map.grid[(int)y][(int)x] == '1');
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

	/* collision X */
	if (!is_wall(game, nx, player->pos_y))
		player->pos_x = nx;

	/* collision Y */
	if (!is_wall(game, player->pos_x, ny))
		player->pos_y = ny;
}
/* Versione precedente:

void move_player(t_game *game, double forward)
{
    double ms;
    double nx;
    double ny;
    double collision_buffer;
    t_player *player;
    double orig_x;
    double orig_y;
    double dx;
    double dy;

    collision_buffer = 0.2;
    player = game->scene->player;
    ms = 0.08;  //Velocita di movimento
    orig_x = player->pos_x;
    orig_y = player->pos_y;
    nx = orig_x + player->dir_x * ms * forward;
    ny = orig_y + player->dir_y * ms * forward;
    dx = nx - orig_x;
    dy = ny - orig_y;

    // if(game->scene->map.grid[(int)player->pos_y][(int) nx] != '1')
    //     player->pos_x = nx;
    // if(game->scene->map.grid[(int)ny][(int)player->pos_x] != '1')
    //     player->pos_y = ny;

    // Controlla X usando il segno del delta di movimento e la y originale
    if (game->scene->map.grid[(int)orig_y][(int)(nx + (dx > 0 ? collision_buffer : -collision_buffer))] != '1')
        player->pos_x = nx;
    // Controlla Y usando il segno del delta di movimento e la x (eventualmente aggiornata)
    if (game->scene->map.grid[(int)(ny + (dy > 0 ? collision_buffer : -collision_buffer))][(int)player->pos_x] != '1')
        player->pos_y = ny;
    game->scene->player = player;
} */

void strafe_player(t_game *game, double right)
{
    double ms;
    double nx;
    double ny;
    t_player *player;

    player = game->scene->player;
    ms = 0.10;  //Velocita di movimento
    nx = player->pos_x + player->plane_x * ms * right;
    ny = player->pos_y + player->plane_y * ms * right;

	//Correzione:
	if (!is_wall(game, nx, player->pos_y))
		player->pos_x = nx;
	if (!is_wall(game, player->pos_x, ny))
		player->pos_y = ny;

    // if(game->scene->map.grid[(int)player->pos_y][(int) nx] != '1')
    //     player->pos_x = nx;
    // if(game->scene->map.grid[(int)ny][(int)player->pos_x] != '1')
    //     player->pos_y = ny;
    // game->scene->player = player;
}

// versione ottimizzata:

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

/* Versione precedente:
void rotate_player(t_game *game, double angle)
{
    double old_dx;
    double old_dy;
    double old_px;
    double old_py;
    t_player *player;

    player = game->scene->player;
    old_dx = player->dir_x;
    old_dy = player->dir_y;
    old_px = player->plane_x;
    old_py = player->plane_y;
    player->dir_x = old_dx * cos(angle) - old_dy * sin(angle);
    player->dir_y = old_dx * sin(angle) + old_dy * cos(angle);
    player->plane_x = old_px * cos(angle) - old_py * sin(angle);
    player->plane_y = old_px * sin(angle) + old_py * cos(angle);
} */
