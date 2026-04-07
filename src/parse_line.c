/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/07 18:19:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_line(char *map_path, t_scene *scene)
{
    int         fd;
    char        *line;
    
    fd = open(map_path, O_RDONLY);
    line_errors(line, fd);
    line = get_next_line(fd);
    line_errors(line, fd);
    parse_textures(line, scene, fd);
	free(line);
}
void parse_textures(char *line, t_scene *scene, int fd)
{
    char        **split;
    int         num_colors;
    
    num_colors = 0;
    split = ft_split(line, ' ');
	if (!split || !split[0])
        line_errors(line, fd);
    while(line)
    {
        split = ft_split(line, ' ');
        if (!split || !split[0])
		{
			//line_errors(line, fd);
			line = get_next_line(fd);
			continue ;
		}
        if(num_colors < 4)
            num_colors = fill_direction(split, scene, num_colors);
        fill_colors()
        line = get_next_line(fd);
    }
    free_split(split);
	free(line);
}

void  line_errors(char *line, int fd)
{
    if (fd < 0)
	{
		perror("open");
		return;
	}
	if (!line)
	{
		printf("file vuoto o non leggibile: %s\n");
        close(fd);
		return;
	}
}
void parse_colors(char **split, t_scene *scene)
{
	if (ft_strncmp(split[0], "F", 2) == 0
		|| ft_strncmp(split[0], "C", 2) == 0)
	{
		char	**rgb_split;
		rgb_split = NULL;
		if (split[1])
			rgb_split = ft_split(split[1], ',');
		if (rgb_split)
		{
			fill_colors(rgb_split, scene, split[0][0]);
			free_split(rgb_split);
		}
	}
}
