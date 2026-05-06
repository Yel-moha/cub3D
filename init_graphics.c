/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:27:09 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/27 14:19:58 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_minimap(t_temp_map *map)
{
	if (!map)
		return (0);
	if (map->mlx)
		mlx_loop_end(map->mlx);
	if (map->img.img_ptr && map->mlx)
		mlx_destroy_image(map->mlx, map->img.img_ptr);
	if (map->win && map->mlx)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free(map);
	return (0);
}

static int	key_hook_minimap(int keycode, t_temp_map *map)
{
	if (keycode == XK_Escape)
		return (close_minimap(map));
	return (0);
}

static void	put_pixel_map(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	fill_rect(t_img *img, int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel_map(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	clear_image(t_img *img, int color)
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
	if (cell == ' ')
		return (0x00000000);
	return (0x00666666);
}

static void	draw_cell(t_temp_map *map, int row, int col, char cell)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = PADDING + map->off_width + (col * map->tile);
	pixel_y = PADDING + map->off_height + (row * map->tile);
	fill_rect(&map->img, pixel_x, pixel_y, map->tile, cell_color(cell));
}

static void	draw_grid_lines(t_temp_map *map, t_scene *scene)
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

static void	draw_grid(t_temp_map *map, t_scene *scene)
{
	int	row;
	int	col;

	row = 0;
	while (row < scene->map.height)
	{
		col = 0;
		while (col < scene->map.width)
		{
			draw_cell(map, row, col, scene->map.grid[row][col]);
			col++;
		}
		row++;
	}
}

static int	init_image_map(t_temp_map *map)
{
	map->img.img_ptr = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!map->img.img_ptr)
		return (0);
	map->img.addr = mlx_get_data_addr(
		map->img.img_ptr,
		&map->img.bpp,
		&map->img.line_len,
		&map->img.endian
	);
	return (1);
}

void	init_graphics(t_temp_map *map, t_scene *scene)
{
	if (!map || !scene)
		return ;
	map->mlx = mlx_init();
	if (!map->mlx)
	{
		free(map);
		return ;
	}
	map->win = mlx_new_window(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "mini_map");
	if (!map->win)
	{
		close_minimap(map);
		return ;
	}
	if (!init_image_map(map))
	{
		close_minimap(map);
		return ;
	}
	clear_image(&map->img, 0x00000000);
	draw_grid(map, scene);
	draw_grid_lines(map, scene);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img_ptr, 0, 0);
	mlx_key_hook(map->win, key_hook_minimap, (void *)map);
	mlx_hook(map->win, 17, 0, close_minimap, (void *)map);
	mlx_loop(map->mlx);
}

