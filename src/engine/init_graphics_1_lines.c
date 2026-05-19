/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics_1_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:45:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/19 22:10:21 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_grid_lines(t_temp_map *map, t_scene *scene)
{
	int	row;
	int	col;
	int	line_x;
	int	line_y;

	col = 0;
	while (col < scene->map.width - 1)
	{
		line_x = PADDING + map->off_width + ((col + 1) * map->tile);
		row = 0;
		while (row < scene->map.height)
		{
			line_y = PADDING + map->off_height + (row * map->tile);
			put_pixel_map(&map->img, line_x, line_y, 0x00FFFFFF);
			row++;
		}
		col++;
	}
}

static void	draw_horizontal_grid_lines(t_temp_map *map, t_scene *scene)
{
	int	row;
	int	col;
	int	line_x;
	int	line_y;

	row = 0;
	while (row < scene->map.height - 1)
	{
		line_y = PADDING + map->off_height + ((row + 1) * map->tile);
		col = 0;
		while (col < scene->map.width)
		{
			line_x = PADDING + map->off_width + (col * map->tile);
			put_pixel_map(&map->img, line_x, line_y, 0x00FFFFFF);
			col++;
		}
		row++;
	}
}

static void	draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			draw_cell(game->mini_map, row, col,
				game->scene->map.grid[row][col]);
			col++;
		}
		row++;
	}
}

void	render_minimap(t_game *game)
{
	clear_image(&(game->mini_map->img), 0x00000000);
	draw_map(game);
	draw_vertical_grid_lines(game->mini_map, game->scene);
	draw_horizontal_grid_lines(game->mini_map, game->scene);
	mlx_put_image_to_window(game->mini_map->mlx, game->mini_map->win,
		game->mini_map->img.img_ptr, 0, 0);
}
