/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 17:10:38 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	j;

	j = 0;
	while (line[j] == '1' || line[j] == '0' || line[j] == ' '
		|| line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
		|| line[j] == 'E')
		j++;
	if ((line[j] == '\n' || line[j] == '\0') && j != 0)
		return (1);
	return (0);
}

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

static void	fill_grid_pass(const char *map_path, t_scene *scene)
{
	int		fd;
	int		grid_i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (line_errors(NULL, fd));
	grid_i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) && grid_i < scene->map.height)
			fill_grid(scene, grid_i++, line);
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

static void free_split_helper(char **split, t_scene *scene, char flag)
{
	fill_colors(split, scene, flag);
	free_split(split);
}

static char *split_more(char **split)
{
	int		i;
	char	*joined;
	char	*tmp;

	if (!split || !split[1])
		return (NULL);
	joined = ft_strdup(split[1]);
	if (!joined)
		return (NULL);
	i = 2;
	while (split[i])
	{
		tmp = ft_strjoin(joined, split[i]);
		free(joined);
		if (!tmp)
			return (NULL);
		joined = tmp;
		i++;
	}
	return (joined);
}

static void	split_error(char **split)
{
	if (!split || !split[0])
	{
		free_split(split);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	parse_colors(char *line, t_scene *scene)
{
	char	**split;
	int		col_code;
	char	**rgb_split;
	char	*joined_rgb;

	split = ft_split(line, ' ');
	split_error(split);
	rgb_split = NULL;
	joined_rgb = NULL;
	if (ft_strncmp(split[0], "F", 2) == 0
		|| ft_strncmp(split[0], "C", 2) == 0)
	{
		joined_rgb = split_more(split);
		if (joined_rgb)
			rgb_split = ft_split(joined_rgb, ',');
		split_error(rgb_split);
		col_code = check_colors_value(rgb_split, split);
		if (col_code == -1)
			error_colors_value(line, rgb_split, scene, joined_rgb);
		if (rgb_split)
			free_split_helper(rgb_split, scene, split[0][0]);
		free(joined_rgb);
	}
	free_split(split);
}
