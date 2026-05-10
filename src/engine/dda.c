/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:31:39 by anacotti          #+#    #+#             */
/*   Updated: 2026/05/09 12:31:42 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;
	
	//game->map = game->scene->map; // Aggiunto da youssef
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
		if (ray->map_y < 0 || ray->map_y >= game->scene->map.height ||
				ray->map_x < 0 || ray->map_x >= game->scene->map.width)
			break ;
		/* RICERCA MURO
		 * Se la cella attuale contiene '1' (muro), hit trovato!
		 * Esci dal loop; possiamo ora calcolare la distanza e renderizzare
		 */
		if(game->scene->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
