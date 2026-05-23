/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:30:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 21:58:33 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_sprite_positions(t_game *game)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			if (game->scene->map.grid[row][col] == 'M')
				count++;
			col++;
		}
		row++;
	}
	game->sprite_count = count;
}

static void	swap_sprite_order(int *order, double *dist, int a, int b)
{
	int		order_tmp;
	double	dist_tmp;

	order_tmp = order[a];
	order[a] = order[b];
	order[b] = order_tmp;
	dist_tmp = dist[a];
	dist[a] = dist[b];
	dist[b] = dist_tmp;
}

void	sort_sprites(int *order, double *dist, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (dist[j] < dist[j + 1])
				swap_sprite_order(order, dist, j, j + 1);
			j++;
		}
		i++;
	}
}
