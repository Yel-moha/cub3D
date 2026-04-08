/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/08 19:15:56 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(const char *map_path, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		line_errors(NULL, fd);
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		parse_textures(line, scene, fd);
		parse_colors(line, scene);
		if(scene->counter == 6)
			count_grid_height(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse_textures(char *line, t_scene *scene, int fd)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0])
		line_errors(line, fd);
	fill_direction(split, scene);
	free_split(split);
}

void	line_errors(char *line, int fd)
{
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (!line)
	{
		printf("file vuoto o non leggibile:\n");
		close(fd);
		return ;
	}
}

void	parse_colors(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
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
	free_split(split);
}
