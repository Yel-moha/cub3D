/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:18:28 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/24 17:00:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_extra_chars_textures(t_scene *scene, char *line, char **split)
{
    int i;

    i = 0;
    while(split[2][i] != '\n' && split[2][i] != '\0')
    {
        if(split[2][i] != ' ')
        {
            free_split(split);
            free(line);
            get_next_line(-1);
            free_scene(scene);
            write(2, "Errore carattere non valido\n", \
                    ft_strlen("Errore carattere non valido\n") + 1);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void    nl_grid_error(char *line)
{
    free(line);
    get_next_line(-1);
	write(2, "Error\nnewline nel mezzo della griglia\n", 38);
	exit(EXIT_FAILURE);
}