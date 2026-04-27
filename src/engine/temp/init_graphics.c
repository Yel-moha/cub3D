/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:27:09 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/27 15:50:46 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cell_color(char cell)
{
	if (cell == '1')
		return (0x00444444);
	if (cell == '0')
		return (0x00D9D9D9);
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (0x0000AA00);
	if (cell == ' ')
		return (0x00000000);
	return (0x00666666);
}

static void	draw_cell(t_game *game, int row, int col, char cell)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	pixel_x = PADDING + game->mini_map->off_width
		+ (col * game->mini_map->tile);
	pixel_y = PADDING + game->mini_map->off_height
		+ (row * game->mini_map->tile);
	y = 0;
	while (y < game->mini_map->tile)
	{
		x = 0;
		while (x < game->mini_map->tile)
		{
			put_pixel(&game->img, pixel_x + x, pixel_y + y, cell_color(cell));
			x++;
		}
		y++;
	}
}

static void	draw_vlines(t_game *game)
{
	int	row;
	int	col;
	int	line_x;
	int	line_y;

	col = 0;
	while (col < game->scene->map.width - 1)
	{
		line_x = PADDING + game->mini_map->off_width
			+ ((col + 1) * game->mini_map->tile);
		row = 0;
		while (row < game->scene->map.height)
		{
			line_y = PADDING + game->mini_map->off_height
				+ (row * game->mini_map->tile);
			put_pixel(&game->img, line_x, line_y, 0x00FFFFFF);
			row++;
		}
		col++;
	}
}

static void	draw_hlines(t_game *game)
{
	int	row;
	int	col;
	int	line_x;
	int	line_y;

	row = 0;
	while (row < game->scene->map.height - 1)
	{
		line_y = PADDING + game->mini_map->off_height
			+ ((row + 1) * game->mini_map->tile);
		col = 0;
		while (col < game->scene->map.width)
		{
			line_x = PADDING + game->mini_map->off_width
				+ (col * game->mini_map->tile);
			put_pixel(&game->img, line_x, line_y, 0x00FFFFFF);
			col++;
		}
		row++;
	}
}

void	init_graphics(t_game *game)
{
	int	row;
	int	col;

	if (!game || !game->mini_map || !game->scene)
		return ;
	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			draw_cell(game, row, col, game->scene->map.grid[row][col]);
			col++;
		}
		row++;
	}
	draw_vlines(game);
	draw_hlines(game);
	free(game->mini_map);
	game->mini_map = NULL;
}
