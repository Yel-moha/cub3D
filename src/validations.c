/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:16:54 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/04 15:48:11 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_direction(char **line, t_tex_paths *pos)
{
    if (ft_strncmp(line[0], "NO", 3) == 0)
        pos->no = ft_strdup(line[1]);
    else if (ft_strncmp(line[0], "SO", 3) == 0)
        pos->so = ft_strdup(line[1]);
    else if (ft_strncmp(line[0], "WE", 3) == 0)
        pos->we = ft_strdup(line[1]);
    else if (ft_strncmp(line[0], "EA", 3) == 0)
        pos->ea = ft_strdup(line[1]);
}

void fill_colors(char **line)
{
    t_rgb *floor;
    t_rgb *cieling;
    
    floor = ft_calloc(sizeof(int), sizeof(t_rgb));
    cieling = ft_calloc(sizeof(int), sizeof(t_rgb));
    if (ft_strncmp(line[0], "F", 3) == 0)
    {
       floor->r = ft_atoi(line[1]);
       floor->g = ft_atoi(line[2]);
       floor->b = ft_atoi(line[3]);
       //floor->value = (r << 16) | (g << 8) | b; // ci pensero dopo a calolarla V=65536R+256G+B
    }
    else if (ft_strncmp(line[0], "C", 3) == 0)
    {
        cieling->r = ft_atoi(line[1]);
        cieling->g = ft_atoi(line[2]);
        cieling->b = ft_atoi(line[3]);
        //cieling->value = (r << 16) | (g << 8) | b; // ci pensero dopo a calolarla V=65536R+256G+B
    }
    print_colors(*floor);
    print_colors(*cieling);
    free_colors(floor);
    free_colors(cieling);
}
