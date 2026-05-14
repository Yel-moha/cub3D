/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:50 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/14 21:50:50 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_line	init_line(t_point p0, t_point p1)
{
	t_line	line;

	line.dx = abs(p1.x - p0.x);
	line.dy = -abs(p1.y - p0.y);
	if (p0.x < p1.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (p0.y < p1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	return (line);
}

void	draw_line(t_img *img, t_point p0, t_point p1, int color)
{
	t_line	line;

	line = init_line(p0, p1);
	while (1)
	{
		put_pixel(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			p0.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			p0.y += line.sy;
		}
	}
}
