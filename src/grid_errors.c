/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:18:28 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/20 15:27:37 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

void check_invalid_chars(t_scene *scene, char *map_path)
{
    (void)scene;
    int i;
    int fd;
    char *line;
    
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
		return (line_errors(NULL, fd));
    line = get_next_line(fd);
    i = 0;
    while(line)
    {
        while(line[i])
        {
        if(ft_isprint(line[i]))
            printf("Errore carattere non valido all'interno della mappa\n");
        }
        i++;
    }
}