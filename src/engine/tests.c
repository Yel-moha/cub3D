/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:23:45 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/25 13:08:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_game *game)
{
    (void)game;
	if (keycode == 65307)
	{
		//free_fractal(fractal);
		exit(0);
    }
	return (0);
}
/*
void	draw(t_game *game)
{
	int	x;
	int	y;
	int	k;

	init_image(game, game->type);
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = -1;
		while (++y < WINDOW_HEIGHT)
		{
			k = compute(game, x, y);
			game->data[y * WINDOW_WIDTH + x] = 0x000000;
			game->data[y * WINDOW_WIDTH + x] = get_color(k, fractal->color_mode);
		}
	}
	execute(game);
}
    */
/*
int	compute_fractal(t_game  *game, int x, int y)
{
	double	real;
    double  

	real = game->player.plane_x + (double)x / WIDTH * \
		(fractal->max_re - fractal->min_re);
	imag = fractal->min_im + (double)y / HEIGHT * \
		(fractal->max_im - fractal->min_im);
	if (fractal->flag == 1)
		return (mandelbrot(real, imag));
	if (fractal->flag == 2)
		return (julia(real, imag, fractal->julia_re, fractal->julia_im));
	return (0);
}
*/
/*
void	execute_fractal(t_game *game)
{
	//mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	mlx_key_hook(game->win, key_hook, (void *)game);
	//mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
	mlx_hook(game->win, 17, 0, close_window, (void *)game);
	//mlx_loop(game->mlx);
}
*/

int	close_window(t_game *game)
{

    (void)game;
	//free_fractal(fractal);
	exit(0);
	return (0);
}