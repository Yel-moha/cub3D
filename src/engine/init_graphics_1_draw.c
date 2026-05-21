/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics_1_draw.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:45:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/19 22:10:18 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_map(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	fill_rect(t_temp_map *map, t_point start, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_map(&map->img, start.x + x, start.y + y, color);
			x++;
		}
		y++;
	}
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_map(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	cell_color(char cell)
{
	if (cell == '1')
		return (0x00444444);
	if (cell == '0')
		return (0x00D9D9D9);
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (0x0000AA00);
	if (cell == 'D')
		return (0x00AA0000); /* closed door: red */
	if (cell == 'O')
		return (0x0000AA00); /* open door: green */
	if (cell == ' ')
		return (0x00000000);
	return (0x00666666);
}

void	draw_cell(t_temp_map *map, int row, int col, char cell)
{
	t_point	start;

	start.x = PADDING + map->off_width + (col * map->tile);
	start.y = PADDING + map->off_height + (row * map->tile);
	fill_rect(map, start, map->tile, cell_color(cell));
}
