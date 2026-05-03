/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 14:57:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/03 14:01:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    /*
    if(game->scene->map.grid[(int)player->pos_y][(int) nx] != '1')
        player->pos_x = nx;
    if(game->scene->map.grid[(int)ny][(int)player->pos_x] != '1')
        player->pos_y = ny;
        */
    // Controlla X usando il segno del delta di movimento e la y originale
    if (game->scene->map.grid[(int)orig_y][(int)(nx + (dx > 0 ? collision_buffer : -collision_buffer))] != '1')
        player->pos_x = nx;
    // Controlla Y usando il segno del delta di movimento e la x (eventualmente aggiornata)
    if (game->scene->map.grid[(int)(ny + (dy > 0 ? collision_buffer : -collision_buffer))][(int)player->pos_x] != '1')
        player->pos_y = ny;
    game->scene->player = player;
}

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
    if(game->scene->map.grid[(int)player->pos_y][(int) nx] != '1')
        player->pos_x = nx;
    if(game->scene->map.grid[(int)ny][(int)player->pos_x] != '1')
        player->pos_y = ny;
    game->scene->player = player;
}

void rotate_player(t_game *game, double angle)
{
    double old_dx;
    double old_px;
    t_player *player;

    player = game->scene->player;
    old_dx = player->dir_x;
    old_px = player->plane_x;
    player->dir_x = old_dx * cos(angle) - player->dir_y * sin(angle);
    player->dir_y = old_dx * sin(angle) + player->dir_y * cos(angle);
    player->plane_x = old_px * cos(angle) - player->plane_y * sin(angle);
    player->plane_y = old_px * sin(angle) + player->plane_y * cos(angle);
}