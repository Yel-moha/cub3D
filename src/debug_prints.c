/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:17:31 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/04 15:46:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_split(char **split)
{
	int i;

	i = 0;
	while (split && split[i])
	{
		printf("token[%d]: %s\n", i, split[i]);
		i++;
	}
}

void print_text_paths(t_tex_paths pos_text)
{
	printf("\npercorso sfondo north e' : %s\n", pos_text.no);
	printf("percorso sfondo south e' : %s\n", pos_text.so);
	printf("percorso sfondo west e' : %s\n", pos_text.we);
	printf("percorso sfondo east e' : %s\n", pos_text.ea);
}

void print_colors(t_rgb colors)
{
	printf("\nqui i colori r g b\n");
	printf("colore r: %d\n", colors.r);
	printf("colore g: %d\n", colors.g);
	printf("colore b: %d\n", colors.b);
}