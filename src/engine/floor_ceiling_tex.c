/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:31:54 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/14 20:59:52 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < WINDOW_HEIGHT / 2)
				put_pixel(&game->img, x, y, game->scene->ceiling.value);
			else
				put_pixel(&game->img, x, y, game->scene->floor.value);
			y++;
		}
		x++;
	}
}

int	load_texture(t_game *game, int i, char *path)
{
	t_img	*t;

	t = &game->tex[i];
	t->img_ptr = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex_w[i], &game->tex_h[i]);
	if (!t->img_ptr)
		return (0);
	t->addr = mlx_get_data_addr(t->img_ptr,
			&t->bpp, &t->line_len, &t->endian);
	if (!t->addr)
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, 0, game->scene->textures.no))
		return (0);
	if (!load_texture(game, 1, game->scene->textures.so))
		return (0);
	if (!load_texture(game, 2, game->scene->textures.we))
		return (0);
	if (!load_texture(game, 3, game->scene->textures.ea))
		return (0);
	return (1);
}
