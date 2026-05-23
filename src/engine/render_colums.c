/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:33 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/11 16:09:32 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	normalize_tex_x(int tex_x, t_ray *ray, int tex_w)
{
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	if (ray->was_hit_vertical && ray->dir_x > 0)
		tex_x = tex_w - tex_x - 1;
	if (!ray->was_hit_vertical && ray->dir_y < 0)
		tex_x = tex_w - tex_x - 1;
	return (tex_x);
}

static void	draw_flat_col(t_game *game, int x, t_draw_col col)
{
	int	color;
	int	y;

	if (col.tex_id == 2 || col.tex_id == 3)
		color = 0x00444444;
	else if (col.tex_id == 4)
		color = 0x008B5A2B;
	else
		color = 0x00BBBBBB;
	y = col.draw_start;
	while (y <= col.draw_end)
	{
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

static void	draw_textured_col(t_game *game, t_ray *ray, int x, \
		t_draw_col col)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_x;
	int		tex_y;

	tex_x = (int)(col.wall_x * (double)game->tex_w[col.tex_id]);
	tex_x = normalize_tex_x(tex_x, ray, game->tex_w[col.tex_id]);
	step = (double)game->tex_h[col.tex_id] / (double)col.line_height;
	tex_pos = (col.draw_start - WINDOW_HEIGHT / 2 + col.line_height / 2)
		* step;
	y = col.draw_start;
	while (y <= col.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->tex_h[col.tex_id])
			tex_y = game->tex_h[col.tex_id] - 1;
		tex_pos += step;
		put_pixel(&game->img, x, y, *(unsigned int *)(game->tex[col.tex_id].addr
				+ tex_y * game->tex[col.tex_id].line_len
				+ tex_x * (game->tex[col.tex_id].bpp / 8)));
		y++;
	}
}

static void	init_draw_col(t_draw_col *col, t_ray *ray, int lh)
{
	col->line_height = lh;
	col->draw_start = -lh / 2 + WINDOW_HEIGHT / 2;
	col->draw_end = lh / 2 + WINDOW_HEIGHT / 2;
	if (col->draw_start < 0)
		col->draw_start = 0;
	if (col->draw_end >= WINDOW_HEIGHT)
		col->draw_end = WINDOW_HEIGHT - 1;
	if (ray->was_hit_vertical)
	{
		if (ray->dir_x > 0)
			col->tex_id = 2;
		else
			col->tex_id = 3;
		col->wall_x = ray->pos_y + ray->perp_dist * ray->dir_y;
	}
	else
	{
		if (ray->dir_y > 0)
			col->tex_id = 1;
		else
			col->tex_id = 0;
		col->wall_x = ray->pos_x + ray->perp_dist * ray->dir_x;
	}
	col->wall_x -= floor(col->wall_x);
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_draw_col	col;
	char		cell;
	int			lh;

	if (!game || !ray)
		return ;
	lh = (int)(WINDOW_HEIGHT / ray->perp_dist);
	init_draw_col(&col, ray, lh);
	cell = game->scene->map.grid[ray->map_y][ray->map_x];
	if (cell == 'D')
		col.tex_id = 4;
	if (!game->tex[col.tex_id].img_ptr || game->tex_w[col.tex_id] <= 0
		|| game->tex_h[col.tex_id] <= 0)
		draw_flat_col(game, x, col);
	else
		draw_textured_col(game, ray, x, col);
}
