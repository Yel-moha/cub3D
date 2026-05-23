/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:05 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 20:22:44 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_player_ns(char c, t_game *game, int row, int col)
{
	game->scene->player->pos_x = col + 0.5;
	game->scene->player->pos_y = row + 0.5;
	if (c == 'S')
	{
		game->scene->player->dir_x = 0;
		game->scene->player->dir_y = 1;
		game->scene->player->plane_x = 0.66;
		game->scene->player->plane_y = 0;
	}
	else if (c == 'N')
	{
		game->scene->player->dir_x = 0;
		game->scene->player->dir_y = -1;
		game->scene->player->plane_x = -0.66;
		game->scene->player->plane_y = 0;
	}
}

void	fill_player_ew(char c, t_game *game, int row, int col)
{
	game->scene->player->pos_x = col + 0.5;
	game->scene->player->pos_y = row + 0.5;
	if (c == 'W')
	{
		game->scene->player->dir_x = -1;
		game->scene->player->dir_y = 0;
		game->scene->player->plane_x = 0;
		game->scene->player->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		game->scene->player->dir_x = 1;
		game->scene->player->dir_y = 0;
		game->scene->player->plane_x = 0;
		game->scene->player->plane_y = 0.66;
	}
}

void	player_init(t_game *game)
{
	int		row;
	int		col;
	char	c;

	if (!game || !game->scene)
		return ;
	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			c = game->scene->map.grid[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (c == 'N' || c == 'S')
					fill_player_ns(c, game, row, col);
				else
					fill_player_ew(c, game, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
}
