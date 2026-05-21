/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:30:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 21:58:13 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_sprite_positions(t_game *game)
{
	int	row;
	int	col;
	int	sprite_i;

	sprite_i = 0;
	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			if (game->scene->map.grid[row][col] == 'M')
			{
				game->sprites[sprite_i].pos_x = col + 0.5;
				game->sprites[sprite_i].pos_y = row + 0.5;
				sprite_i++;
			}
			col++;
		}
		row++;
	}
}

void	init_sprites(t_game *game)
{
	if (!game || !game->scene)
		return ;
	count_sprite_positions(game);
	if (game->sprite_count <= 0)
		return ;
	game->sprites = ft_calloc(game->sprite_count, sizeof(t_sprite));
	if (!game->sprites)
		cleanup_and_exit(game, 0);
	fill_sprite_positions(game);
}
