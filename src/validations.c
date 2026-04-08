/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:16:54 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/08 11:42:59 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int *fill_direction(char **line, t_scene *scene, int *num_colors)
{
    if (!line || !line[0] || !line[1])
        return (0);
    if (ft_strncmp(line[0], "NO", 3) == 0)
    {
        scene->textures.no = ft_strdup(line[1]);
        num_colors++;
    }
    else if (ft_strncmp(line[0], "SO", 3) == 0)
    {
        scene->textures.so = ft_strdup(line[1]);
        num_colors++;
    }
    else if (ft_strncmp(line[0], "WE", 3) == 0)
    {
        scene->textures.we = ft_strdup(line[1]);
        num_colors++;
    }
    else if (ft_strncmp(line[0], "EA", 3) == 0)
    {
        scene->textures.ea = ft_strdup(line[1]);
        num_colors++;
    }
   return (num_colors);
}

void fill_colors(char **line, t_scene *scene, char f_or_c)
{
    if (!line || !line[0] || !line[1] || !line[2])
            return ;
    if(f_or_c == 'F')
    {
        scene->floor.r = ft_atoi(line[0]);
        scene->floor.g = ft_atoi(line[1]);
        scene->floor.b = ft_atoi(line[2]);
        //scene->floor.value = (r << 16) | (g << 8) | b; // ci pensero dopo a calolarla V=65536R+256G+B
    }
    else if(f_or_c == 'C')
    {
        scene->ceiling.r = ft_atoi(line[0]);
        scene->ceiling.g = ft_atoi(line[0]);
        scene->ceiling.b = ft_atoi(line[0]);
        //scene->ceiling.value = (r << 16) | (g << 8) | b; // ci pensero dopo a calolarla V=65536R+256G+B
    }
    else 
        return ;
}
