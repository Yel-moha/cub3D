/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:54:03 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/14 13:21:02 by yel-moha         ###   ########.fr       */
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
	free_split(split);
	free_scene(scene);
	write(1, "double path\n", ft_strlen("double path") + 1);
	if(flag == 'F')
		write(2, "Errore doppio path per il colore dei floor\n", \
			ft_strlen("Errore doppio path per il colore dei floor") + 1);
	if(flag == 'C')
		write(2, "Errore doppio path per il colore dei cieling\n", \
			ft_strlen("Errore doppio path per il colore dei cieling") + 1);
	//QUi occorre ancora fare il free della *line, e andrebbe passata da parseline
	exit(EXIT_FAILURE); // Termina il programma con codice di errore (di solito 1)
}

void error_colors_value(char *line, char **rgb_split)
{
	free(line);
	free_split(rgb_split);
	write(2, "Errore valore colori\n", \
			ft_strlen("Errore valore colori\n") + 1);
	exit(EXIT_FAILURE); // Termina il programma con codice di errore (di solito 1)
}