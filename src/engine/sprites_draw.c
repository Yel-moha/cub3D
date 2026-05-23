/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:30:00 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/21 21:59:03 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_sprite_lists(t_game *game, int **order, double **dist)
{
	int	i;

	*order = malloc(sizeof(int) * game->sprite_count);
	*dist = malloc(sizeof(double) * game->sprite_count);
	if (!*order || !*dist)
	{
		free(*order);
		free(*dist);
		return (0);
	}
	i = 0;
	while (i < game->sprite_count)
	{
		(*order)[i] = i;
		(*dist)[i] = (game->scene->player->pos_x - game->sprites[i].pos_x)
			* (game->scene->player->pos_x - game->sprites[i].pos_x)
			+ (game->scene->player->pos_y - game->sprites[i].pos_y)
			* (game->scene->player->pos_y - game->sprites[i].pos_y);
		i++;
	}
	sort_sprites(*order, *dist, game->sprite_count);
	return (1);
}

static int	get_sprite_tex_id(t_game *game)
{
	int	frame;
	int	tex_id;

	frame = ((int)(game->elapsed_time * 8.0)) % SPRITE_FRAME_COUNT;
	tex_id = SPRITE_TEX_BASE + frame;
	if (!game->tex[tex_id].img_ptr || game->tex_w[tex_id] <= 0
		|| game->tex_h[tex_id] <= 0)
		return (-1);
	return (tex_id);
}

void	render_sprites(t_game *game)
{
	int				*order;
	double			*dist;
	int				i;
	t_sprite_draw	draw;

	if (!game || !game->sprites || game->sprite_count <= 0 || !game->z_buffer)
		return ;
	if (!init_sprite_lists(game, &order, &dist))
		return ;
	draw.tex_id = get_sprite_tex_id(game);
	if (draw.tex_id < 0)
	{
		free(order);
		free(dist);
		return ;
	}
	i = 0;
	while (i < game->sprite_count)
	{
		render_single_sprite(game, order[i], &draw);
		i++;
	}
	free(order);
	free(dist);
}
