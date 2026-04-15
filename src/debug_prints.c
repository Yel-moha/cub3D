/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:17:31 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 11:54:40 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		printf("token[%d]: %s\n", i, split[i]);
		i++;
	}
}

void	print_text_paths(t_scene scene)
{
	printf("\npercorso sfondo north e' : %s\n", scene.textures.no);
	printf("percorso sfondo south e' : %s\n", scene.textures.so);
	printf("percorso sfondo west e' : %s\n", scene.textures.we);
	printf("percorso sfondo east e' : %s\n", scene.textures.ea);
}

void	print_colors(t_scene scene)
{
	printf("\nQui la lista dei colori floor e cieling \n");
	printf("r = %d\n", scene.floor.r);
	printf("g = %d\n", scene.floor.g);
	printf("b = %d\n", scene.floor.b);
	printf("value  = %d\n", scene.floor.value);
	printf("\nQui la lista dei colori floor e cieling \n");
	printf("r = %d\n", scene.ceiling.r);
	printf("g = %d\n", scene.ceiling.g);
	printf("b = %d\n", scene.ceiling.b);
	printf("value = %d\n", scene.ceiling.value);
}
void print_player(t_scene scene)
{
	printf("La direzione del giocatore (spawn) e' %c\n", scene.player.spawn);
}

void print_map(t_scene scene)
{
	printf("la largezza della mappa : %d\n", scene.map.width);
	printf("la lunghezza della mappa : %d\n", scene.map.height);
	printf("la flag e' : %s\n", scene.flag);
}

void print_grid(t_scene scene)
{
	printf("la larghezza della griglia è %d\n", scene.map.width);
	int i;
	int j;

	i = 0;
	while (i < scene.map.height)
	{
		printf("row[%d]: ", i);
		j = 0;
		while (j < scene.map.width)
		{
			if (scene.map.grid[i][j] == ' ')
				printf(".");
			else
				printf("%c", scene.map.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}