#include "cub3d.h"

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
