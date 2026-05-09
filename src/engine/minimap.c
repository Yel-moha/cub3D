#include "cub3d.h"

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
