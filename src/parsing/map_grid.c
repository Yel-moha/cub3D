/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/11 14:57:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_symb(char *line, t_scene *scene)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			count++;
			c = line[i];
		}
		i++;
	}
	if (count == 1)
		scene->player->spawn = c;
	return (count);
}

void	count_grid_height(char *line, t_scene *scene)
{
	size_t	j;

	j = 0;
	scene->pos += count_symb(line, scene);
	if (scene->pos > 1)
		error_spawn_player(line, scene);
	while (line[j] == '1' || line[j] == '0' || line[j] == ' '
		|| line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
		|| line[j] == 'E')
		j++;
	if ((line[j] == '\n' || line[j] == '\0') && j != 0)
		scene->map.height++;
}

int	max_line(char *line, t_scene *scene)
{
	int	j;

	j = 0;
	while ((line[j] == '1' || line[j] == '0' || line[j] == ' '
			|| line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
			|| line[j] == 'E') && scene->counter == 6)
		j++;
	return (j);
}

void	fill_grid(t_scene *scene, int i, char *line)
{
	int	j;

	j = 0;
	while (line[j] != '\0' && line[j] != '\n')
	{
		if (line[j] == ' ')
			scene->map.grid[i][j] = ' ';
		else
			scene->map.grid[i][j] = line[j];
		j++;
	}
	while (j < scene->map.width)
	{
		scene->map.grid[i][j] = ' ';
		j++;
	}
	scene->map.grid[i][scene->map.width] = '\0';
}

void	allocate_grid(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->map.height > 0)
		scene->map.grid = ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!scene->map.grid)
		return ;
	while (i < scene->map.height)
	{
		scene->map.grid[i] = ft_calloc(scene->map.width + 1, sizeof(char));
		if (!scene->map.grid[i])
			return ;
		scene->map.grid[i][scene->map.width] = '\0';
		i++;
	}
}
