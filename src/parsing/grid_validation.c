/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:25:04 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_border_line_closed(char *line)
{
	int	j;

	j = 0;
	while (line[j] == '1' || line[j] == ' ')
		j++;
	return (j);
}

static int	is_interior_line_valid(char *line)
{
	int	j;
	int	end_line;

	j = 0;
	end_line = line_len_no_nl(line);
	while (line[j] == ' ')
		j++;
	if (j == end_line || line[j] != '1')
		return (0);
	while (end_line > 0 && line[end_line - 1] == ' ')
		end_line--;
	if (end_line <= 0 || line[end_line - 1] != '1')
		return (0);
	return (1);
}

static int	validate_middle_rows(char **rows, t_scene *scene)
{
	int	i;

	i = 1;
	while (i < scene->map.height - 1)
	{
		if (!validate_line(rows[i], i, scene))
			return (0);
		if (!middle_row_is_closed(rows, scene->map.height, i))
			return (0);
		i++;
	}
	return (1);
}

int	validate_borders(const char *map_path, t_scene *scene)
{
	char	**rows;
	int		loaded;

	rows = ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!rows)
		return (0);
	loaded = load_map_rows(map_path, scene, rows);
	if (loaded != scene->map.height || !validate_line(rows[0], 0, scene)
		|| !validate_line(rows[scene->map.height - 1],
			scene->map.height - 1, scene))
		return (free_rows(rows, loaded), 0);
	if (!validate_middle_rows(rows, scene))
		return (free_rows(rows, loaded), 0);
	free_rows(rows, loaded);
	return (1);
}

int	validate_line(char *line, int index, t_scene *scene)
{
	if (index == 0 || index == scene->map.height - 1)
		return (is_border_line_closed(line) == line_len_no_nl(line));
	return (is_interior_line_valid(line));
}
