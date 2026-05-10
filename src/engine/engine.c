/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:31:51 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/09 15:27:43 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

/*
✔ player + direzione
✔ raycasting senza texture (muri colorati)
✔ DDA stabile
✔ correzione distanza
✔ rendering colonne
✔ texture
✔ movimento player
✔ collisioni
*/

//debug
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// void	player_init(t_game *game)
// {

// }

void	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(
		game->img.img_ptr,
		&game->img.bpp,
		&game->img.line_len,
		&game->img.endian
	);
}

void	player_init(t_game *game)
{
	int row;
	int col;
	char c;

	if (!game || !game->scene)
		return ;
	row = 0;
	while (row < game->scene->map.height)
	{
		col = 0;
		while (col < game->scene->map.width)
		{
			c = game->scene->map.grid[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (c == 'N' || c == 'S')
					fill_player_ns(c, game, row, col);
				else
					fill_player_ew(c, game, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
}

void fill_player_ns(char c, t_game *game, int row, int col)
{
	/* position at cell center */
	game->scene->player->pos_x = col + 0.5;
	game->scene->player->pos_y = row + 0.5;
	if (c == 'N')
	{ 
	game->scene->player->dir_x = -1;
	game->scene->player->dir_y = 0;
	game->scene->player->plane_x = 0;
	game->scene->player->plane_y = 0.66;
	}
	else if (c == 'S') 
	{
	game->scene->player->dir_x = 1;
	game->scene->player->dir_y = 0;
	game->scene->player->plane_x = 0;
	game->scene->player->plane_y = -0.66;
	}
}

void fill_player_ew(char c, t_game *game,  int row, int col)
{
	/* position at cell center */
	game->scene->player->pos_x = col + 0.5;
	game->scene->player->pos_y = row + 0.5;
	if (c == 'E')
	{
	game->scene->player->dir_x = 0; 
	game->scene->player->dir_y = 1;
	game->scene->player->plane_x = 0.66;
	game->scene->player->plane_y = 0;
	}
	else if (c == 'W')
	{
	game->scene->player->dir_x = 0;
	game->scene->player->dir_y = -1;
	game->scene->player->plane_x = -0.66;
	game->scene->player->plane_y = 0;
	}
}

// void	texture_loading()
// {
// 	while()
// 	{
// 		mlx_xpm_file_to_image();
// 		mlx_get_data_addr();
// 	}
// }

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;
	t_scene *scene;

	scene = game->scene;
	
	/* TRASFORMAZIONE COORDINATE SCHERMO -> CAMERA SPACE
	 * camera_x normalizza x [0, WINDOW_WIDTH] -> [-1, 1]
	 * -1 = bordo sinistro schermo
	 *  0 = centro (allineato con player->dir)
	 * +1 = bordo destro schermo
	 */
	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	
	/* DIREZIONE DEL RAGGIO
	 * rayDir = playerDir + camera_x * camera_plane
	 * Combinando dir (forward) + plane (camera width) * offset (camera_x)
	 * otteniamo un raggio diverso per ogni colonna dello schermo
	 * camera_x negativo = raggio deviato a sinistra
	 * camera_x positivo = raggio deviato a destra
	 */
	ray->dir_x = scene->player->dir_x + scene->player->plane_x * camera_x;
	ray->dir_y = scene->player->dir_y + scene->player->plane_y * camera_x;
	
	/* POSIZIONE INIZIALE DEL RAGGIO: dove il giocatore si trova nel mondo
	 * player->pos_x/pos_y è al centro della cella + 0.5 (vedi player_init)
	 */
	ray->pos_x = scene->player->pos_x;
	ray->pos_y = scene->player->pos_y;
	
	/* COORDINATE DELLA CELLA SULLA MAPPA
	 * Converte la posizione float in indice grid [0, map.width/height]
	 * Usato dalla DDA per accedere a map.grid[map_y][map_x]
	 */
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	
	/* DELTA DISTANCE: distanza lungo il raggio per attraversare UNA cella
	 * delta_x = |1 / dir_x| = lunghezza raggio tra due linee verticali di griglia
	 * delta_y = |1 / dir_y| = lunghezza raggio tra due linee orizzontali di griglia
	 * Valori assoluti perché ci interessa solo la magnitudine
	 * 
	 * Se dir_x = 0 (raggio verticale), non attraverserà mai una linea verticale
	 * quindi delta_x = 1e30 (pseudo-infinito) per escluderlo dal confronto DDA
	 */
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;
	
	game->map = game->scene->map; // Aggiunto da youssef
	hit = 0;
	
	/* INIZIALIZZAZIONE PASSO E DISTANZA ORIZZONTALE (X)
	 * step_x: -1 se il raggio va a sinistra (dir_x < 0), +1 se va a destra
	 * side_dist_x: distanza dal punto di partenza fino al PRIMO bordo verticale
	 *   - Se dir_x < 0: frazione della cella (pos_x - map_x) * delta_x = distanza al bordo sinistro
	 *   - Else: distanza fino al prossimo bordo destro = (map_x + 1 - pos_x) * delta_x
	 */
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_x;
	}

	/* INIZIALIZZAZIONE PASSO E DISTANZA VERTICALE (Y)
	 * Stessa logica di X ma per l'asse verticale
	 */
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_y;
	}
	
	/* LOOP DDA (Digital Differential Analyzer)
	 * Itera attraverso la griglia della mappa fino a trovare un muro ('1')
	 * Ad ogni iterazione:
	 *   1. Confronta side_dist_x e side_dist_y
	 *   2. Avanza nella direzione con distanza minore (cioè il prossimo bordo più vicino)
	 *   3. Aggiorna la cella corrente (map_x o map_y)
	 *   4. Somma il delta corrispondente alla side_dist per la prossima iterazione
	 *   5. Segna quale lato è stato colpito (verticale o orizzontale)
	 */
	while(hit == 0)
	{
		/* Se il prossimo bordo verticale è più vicino del prossimo bordo orizzontale */
		if(ray->side_dist_x < ray->side_dist_y)
		{
			/* Avanza X: aggiungi delta_x, incremente map_x, segna hit verticale */
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->was_hit_vertical = 1;
		}
		else
		{
			/* Altrimenti avanza Y: aggiungi delta_y, incrementa map_y, segna hit orizzontale */
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->was_hit_vertical = 0;
		}
		/* VERIFICA CONFINI DELLA MAPPA
		 * Se la cella attuale esce dai limiti della mappa, esci dal loop
		 * (il raggio ha raggiunto il confine senza trovare un muro)
		 */
		if (ray->map_y < 0 || ray->map_y >= game->map.height ||
				ray->map_x < 0 || ray->map_x >= game->map.width)
			break ;
		/* RICERCA MURO
		 * Se la cella attuale contiene '1' (muro), hit trovato!
		 * Esci dal loop; possiamo ora calcolare la distanza e renderizzare
		 */
		if(game->scene->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
/*Aggiunti 29/04/2026 Da youssef*/
void	compute_distance(t_game *game, t_ray *ray)
{
	(void)game;
	if (!ray)
		return ;
	if (ray->was_hit_vertical)
		ray->perp_dist = ray->side_dist_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_y;
	if (ray->perp_dist <= 0)
		ray->perp_dist = 1e-6;
}

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

static void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	while (1)
	{
		put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_rays_on_minimap(t_game *game)
{
	int i;
	int px, py, tx, ty;
	int tile;
	int map_w_px;
	t_scene *scene;

	if (!game || !game->mini_map || !game->scene)
		return ;
	scene = game->scene;
	tile = game->mini_map->tile;
	map_w_px = scene->map.width * tile;
	px = PADDING + game->mini_map->off_width
		+ (map_w_px - (int)(scene->player->pos_x * tile));
	py = PADDING + game->mini_map->off_height + (int)(scene->player->pos_y * tile);
	i = 0;
	while (i < WINDOW_WIDTH && i < (int)(sizeof(*game->rays) * WINDOW_WIDTH))
	{
		tx = PADDING + game->mini_map->off_width
			+ (map_w_px - ((game->rays[i].map_x * tile) + tile / 2));
		ty = PADDING + game->mini_map->off_height + game->rays[i].map_y * tile + tile / 2;
		draw_line(&game->img, px, py, tx, ty, 0x00FF0000);
		i++;
	}
}
/******************************************************** */
int	render_frame(void *param)
{
	t_game	*game;
	int		x;
	game = (t_game *)param;

	/* compute delta time and process held keys each frame */
	{
		struct timeval tv;
		double now;
		double dt;

		gettimeofday(&tv, NULL);
		now = tv.tv_sec + tv.tv_usec / 1e6;
		if (game->last_time <= 0.0)
			dt = 1.0 / 60.0;
		else
			dt = now - game->last_time;
		if (dt <= 0 || dt > 0.5)
			dt = 1.0 / 60.0;
		game->last_time = now;
		handle_keys(game, dt);
	}

	// debug - pulizia schermo (nero)
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
		((int *)game->img.addr)[i] = 0x000000;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, &game->rays[x], x);
		perform_dda(game, &game->rays[x]);
		compute_distance(game, &game->rays[x]);
		draw_column(game, &game->rays[x], x);
		x++;
	}
	draw_grill(game);

	/* draw rays overlay on minimap */
	draw_rays_on_minimap(game);

	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return(0);
}

void	engine_init(t_game *game)
{
	game->map = game->scene->map; // Aggiunto da youssef
	
	game->mlx = mlx_init();
	if (!game->mlx)
		return ; // TO-DO clean_exit();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return ; // TO-DO clean_exit();

	init_image(game);
	player_init(game);

	/* Qui preveremo a caricare le textures
	if (!load_textures(game))
	{
		// warning - textures not loaded, continue with flat colors
		// write(1, "Warning: textures not loaded\n", 25); 
	}
	//texture_loading(game);
	*/

	game->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (!game->rays)
		return ; // TO-DO clean_exit();

	/* init key states and frame timer */
	for (int i = 0; i < 65536; i++)
		game->keys[i] = 0;
	game->last_time = 0.0;

	mlx_loop_hook(game->mlx, render_frame, game);


	/*Questo aggiunto da youssef*/
	//Gestione della chiusura della finestra usando ESC e X

	/* Use KeyPress/KeyRelease hooks so held keys work */
	mlx_hook(game->win, 2, 1L<<0, key_press, (void *)game);
	mlx_hook(game->win, 3, 1L<<1, key_release, (void *)game);
	mlx_hook(game->win, 17, 0, close_window, (void *)game);

	////////////
	/*Fine parte aggiunta da youssef*/

	
	mlx_loop(game->mlx);

	// render_frame è dove fai:
	// raycasting
	// disegno

	// raycasting();
	// dda(game);
	// perp_wall_dist();
}
