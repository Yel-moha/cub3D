/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 18:31:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int	count_pass_line(t_scene *scene, int fd, char *line)
{
	int	line_len;

	line_len = max_line(line, scene);
	if (line_len > scene->map.width)
		scene->map.width = line_len;
	parse_textures(line, scene, fd);
	parse_colors(line, scene);
	if (scene->counter == 6 && is_map_line(line))
	{
		parse_grid(scene, fd, line);
		return (1);
	}
	return (0);
}

static void	count_grid_pass(const char *map_path, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (line_errors(NULL, fd));
	line = get_next_line(fd);
	while (line)
	{
		if (count_pass_line(scene, fd, line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}


void	parse_line(const char *map_path, t_scene *scene)
{
	count_grid_pass(map_path, scene);
	if (scene->map.letta != 1)
		return ;
	allocate_grid(scene);
	scene->map.letta = 2;
	fill_grid_pass(map_path, scene);
}

