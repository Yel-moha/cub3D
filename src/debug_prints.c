/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:17:31 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/09 15:38:43 by yel-moha         ###   ########.fr       */
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
	printf("la flag e' : %s\n", scene.flag);
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
