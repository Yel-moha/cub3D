/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:30:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 21:57:13 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sprite_prepare(t_game *game, int index, t_sprite_draw *draw)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;

	sprite_x = game->sprites[index].pos_x - game->scene->player->pos_x;
	sprite_y = game->sprites[index].pos_y - game->scene->player->pos_y;
	inv_det = 1.0 / (game->scene->player->plane_x * game->scene->player->dir_y
			- game->scene->player->dir_x * game->scene->player->plane_y);
	transform_x = inv_det * (game->scene->player->dir_y * sprite_x
			- game->scene->player->dir_x * sprite_y);
	draw->transform_y = inv_det * (-game->scene->player->plane_y * sprite_x
			+ game->scene->player->plane_x * sprite_y);
	if (draw->transform_y <= 0.0)
		return (0);
	draw->screen_x = (int)((WINDOW_WIDTH / 2.0)
			* (1.0 + transform_x / draw->transform_y));
	return (1);
}

static void	sprite_box_init(t_sprite_draw *draw, t_sprite_box *box)
{
	box->height = abs((int)(WINDOW_HEIGHT / draw->transform_y));
	box->width = box->height;
	box->y_start = -box->height / 2 + WINDOW_HEIGHT / 2;
	if (box->y_start < 0)
		box->y_start = 0;
	box->y_end = box->height / 2 + WINDOW_HEIGHT / 2;
	if (box->y_end >= WINDOW_HEIGHT)
		box->y_end = WINDOW_HEIGHT - 1;
	box->x_start = -box->width / 2 + draw->screen_x;
	if (box->x_start < 0)
		box->x_start = 0;
	box->x_end = box->width / 2 + draw->screen_x;
	if (box->x_end >= WINDOW_WIDTH)
		box->x_end = WINDOW_WIDTH - 1;
}

static void	draw_sprite_column(t_game *game, t_sprite_draw *draw,
		int stripe, t_sprite_box *box)
{
	int		tex_x;
	int		tex_y;
	int		color;
	int		y;
	double	d;

	tex_x = (int)((stripe - (-box->width / 2 + draw->screen_x))
			* game->tex_w[draw->tex_id] / (double)box->width);
	if (tex_x < 0 || tex_x >= game->tex_w[draw->tex_id])
		return ;
	y = box->y_start;
	while (y <= box->y_end)
	{
		d = y * 256 - WINDOW_HEIGHT * 128 + box->height * 128;
		tex_y = (int)((d * game->tex_h[draw->tex_id]) / box->height / 256);
		if (tex_y >= 0 && tex_y < game->tex_h[draw->tex_id])
		{
			color = *(unsigned int *)(game->tex[draw->tex_id].addr
					+ tex_y * game->tex[draw->tex_id].line_len
					+ tex_x * (game->tex[draw->tex_id].bpp / 8));
			if (color != 0)
				put_pixel(&game->img, stripe, y, color);
		}
		y++;
	}
}

void	render_single_sprite(t_game *game, int index, t_sprite_draw *draw)
{
	t_sprite_box	box;
	int				stripe;

	if (!sprite_prepare(game, index, draw))
		return ;
	if (!game->tex[draw->tex_id].img_ptr || game->tex_w[draw->tex_id] <= 0
		|| game->tex_h[draw->tex_id] <= 0)
		return ;
	sprite_box_init(draw, &box);
	stripe = box.x_start;
	while (stripe <= box.x_end)
	{
		if (draw->transform_y < game->z_buffer[stripe])
			draw_sprite_column(game, draw, stripe, &box);
		stripe++;
	}
}
