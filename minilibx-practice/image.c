
# include "minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <complex.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100


void	execute_fractal(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	mlx_key_hook(fractal->win, key_hook, (void *)fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
	mlx_hook(fractal->win, 17, 0, close_window, (void *)fractal);
	mlx_loop(fractal->mlx);
}
