#include "cub3d.h"

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int line_height;
	int draw_start;
	int draw_end;
	int y;
	if (!game || !ray)
		return ;
	/* compute column extents */
	line_height = (int)(WINDOW_HEIGHT / ray->perp_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;

	/* compute exact hit position on the wall */
	double wall_x;
	if (ray->was_hit_vertical)
		wall_x = ray->pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);

	/* select texture id: 0=NO,1=SO,2=WE,3=EA */
	int tex_id;
	if (ray->was_hit_vertical)
	{
		if (ray->dir_x > 0)
			tex_id = 2; /* WE */
		else
			tex_id = 3; /* EA */
	}
	else
	{
		if (ray->dir_y > 0)
			tex_id = 1; /* SO */
		else
			tex_id = 0; /* NO */
	}

	t_img *t = &game->tex[tex_id];
	int tex_w = game->tex_w[tex_id];
	int tex_h = game->tex_h[tex_id];
	if (!t->img_ptr || tex_w <= 0 || tex_h <= 0)
	{
		/* fallback: flat color */
		int color = ray->was_hit_vertical ? 0x00444444 : 0x00BBBBBB;
		for (y = draw_start; y <= draw_end; y++)
			put_pixel(&game->img, x, y, color);
		return ;
	}

	/* texture X coordinate */
	int tex_x = (int)(wall_x * (double)tex_w);
	/* correct orientation for some faces */
	if (ray->was_hit_vertical && ray->dir_x > 0)
		tex_x = tex_w - tex_x - 1;
	if (!ray->was_hit_vertical && ray->dir_y < 0)
		tex_x = tex_w - tex_x - 1;

	/* step in texture per screen pixel */
	double step = (double)tex_h / (double)line_height;
	double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

	for (y = draw_start; y <= draw_end; y++)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex_h) tex_y = tex_h - 1;
		tex_pos += step;
		unsigned int color = *(unsigned int *)(t->addr + tex_y * t->line_len + tex_x * (t->bpp / 8));
		if (ray->was_hit_vertical)
			color = (color >> 1) & 0x7F7F7F; /* simple shading */
		put_pixel(&game->img, x, y, color);
	}
}
