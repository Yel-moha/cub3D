/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/21 21:21:17 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blank_line(char *line)
{
	int	j;

	j = 0;
	if (!line)
		return (1);
	while (line[j] == ' ' || line[j] == '\n' || line[j] == '\t'
		|| line[j] == '\r')
		j++;
	return (line[j] == '\0');
}

void	parse_grid(t_scene *scene, int fd, char *line)
{
	int	line_len;

	line_errors(line, fd);
	while (line && scene->counter >= 6)
	{
		if (is_blank_line(line))
			nl_grid_error(line, scene);
		if (is_map_line(line))
		{
			line_len = max_line(line, scene);
			if (line_len > scene->map.width)
				scene->map.width = line_len;
			count_grid_height(line, scene);
		}
		else
			nl_grid_error(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	scene->map.letta = 1;
}

int	is_map_line(char *line)
{
	int	j;
	int	end;

	j = 0;
	end = ft_strlen(line);
	if (end > 0 && line[end - 1] == '\n')
		end--;
	while (line[j] == '1' || line[j] == '0' || line[j] == ' '
		|| line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
		|| line[j] == 'E' || line[j] == 'D' || line[j] == 'O'
		|| line[j] == 'M')
		j++;
	if (j == end && j != 0)
		return (1);
	return (0);
}

void	fill_grid_pass(const char *map_path, t_scene *scene)
{
	int		fd;
	int		grid_i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (line_errors(NULL, fd));
	grid_i = 0;
	line = get_next_line(fd);
	if (scene->pos == 0)
		error_spawn_player(line, scene);
	while (line)
	{
		if (is_map_line(line) && grid_i < scene->map.height)
			fill_grid(scene, grid_i++, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	print_grid(t_scene scene)
{
	int	i;
	int	j;

	printf("la larghezza della griglia è %d\n", scene.map.width);
	i = 0;
	while (i < scene.map.height)
	{
		printf("row[%d]: ", i);
		j = 0;
		while (j < scene.map.width)
		{
			if (scene.map.grid[i][j] == ' ')
				printf(".");
			else
				printf("%c", scene.map.grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
