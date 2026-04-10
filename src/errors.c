/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:54:03 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/10 13:20:03 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map_errors(char *line)
{
	if (!line)
		return (0);
	return (1);
}

void double_color_path(char flag, t_scene *scene, char **split)
{
	(void)flag;
	free_split(split);
	free_scene(scene);
	write(1, "double 'F' path\n", ft_strlen("double 'F' path") + 1);
	write(2, "Errore doppio path per il colore dei floor\n", \
		ft_strlen("Errore doppio path per il colore dei floor") + 1);
	exit(EXIT_FAILURE); // Termina il programma con codice di errore (di solito 1)
}