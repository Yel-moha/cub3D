/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/27 12:46:37 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int	count_pass_line(t_scene *scene, int fd, char *line)
{
	int	line_len;

	line_len = max_line(line, scene);  //Torna la lunghezza della singola linea della griglia
	if (line_len > scene->map.width)
		scene->map.width = line_len; //Aggiorno la larghezza della griglia con la linea più lunga della griglia
	parse_textures(line, scene, fd);
	parse_colors(line, scene);
	error_extra_line_map(line, scene);
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
		//check_invalid_chars(scene, line);
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
	if (!validate_borders(map_path, scene))
	{
		write(2, "Errore mappa non chiusa\n", 24);
		scene->map.width = 0;
		scene->map.height = 0;
		scene->map.letta = 0;
		return ;
	}
	allocate_grid(scene);
	scene->map.letta = 2;
	fill_grid_pass(map_path, scene);
}
