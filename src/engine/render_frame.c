/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:32:42 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/14 22:13:48 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	update_time(t_game *game)
{
	struct timeval	tv;
	double			now;
	double			dt;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec + tv.tv_usec / 1e6;
	if (game->last_time <= 0.0)
		dt = 1.0 / 60.0;
	else
		dt = now - game->last_time;
	if (dt <= 0 || dt > 0.5)
		dt = 1.0 / 60.0;
	game->last_time = now;
	return (dt);
}

static void	handle_keys_frame(t_game *game)
{
	double	dt;

	dt = update_time(game);
	handle_keys(game, dt);
}

static void	render_scene(t_game *game)
{
	int	x;

	draw_floor_ceiling(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, &game->rays[x], x);
		perform_dda(game, &game->rays[x]);
		compute_distance(game, &game->rays[x]);
		draw_column(game, &game->rays[x], x);
		x++;
	}
}

static void	render_overlays(t_game *game)
{
	draw_grill(game);
	draw_rays_on_minimap(game);
	if (game->mini_map)
	{
		free(game->mini_map);
		game->mini_map = NULL;
	}
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_keys_frame(game);
	render_scene(game);
	render_overlays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

