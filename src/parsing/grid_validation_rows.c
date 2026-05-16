/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation_rows.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rows(char **rows, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(rows[i]);
		i++;
	}
	free(rows);
}

int	load_map_rows(const char *map_path, t_scene *scene, char **rows)
{
	int		fd;
	int		grid_i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (line_errors(NULL, fd), -1);
	grid_i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) && grid_i < scene->map.height)
			rows[grid_i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (grid_i);
}
