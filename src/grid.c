/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:01:48 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 17:04:43 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void copy_original_grid(t_scene *scene)
{
    char **grid_copy;
    int i;

    i = 0;
    if(scene->map.height > 0)
        grid_copy = malloc(sizeof(char *) * scene->map.height + 1);
    if(!scene->map.grid)
        return ;
    grid_copy[scene->map.height] = "\0";
    while(i < scene->map.height)
    {
       grid_copy[i] = malloc(sizeof(char) * scene->map.width + 1);
        if(!scene->map.grid[i])
            return ;
        grid_copy[i][scene->map.width] = '\0';
        i++;
    }
}
void	parse_grid(t_scene *scene, int fd, char *line)
{
	if (fd < 0)
	{
		line_errors(NULL, fd);
		return ;
	}
    while (line && scene->counter >= 6)
    {
        count_grid_height(line, scene);
        free(line);
        line = get_next_line(fd);
    }
    scene->map.letta = 1;
}