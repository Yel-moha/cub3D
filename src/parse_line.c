/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/14 16:17:11 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(const char *map_path, t_scene *scene)
{
	int		fd;
	int		line_len;
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
		line_len = max_line(line, scene);
		if (line_len > scene->map.width)
			scene->map.width = line_len;
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
	free_split(split);
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
	
	split = ft_split(line, ' ');
	split_error(split);
	if (ft_strncmp(split[0], "F", 2) == 0
		|| ft_strncmp(split[0], "C", 2) == 0)
	{
		char	**rgb_split;
		char	*joined_rgb;
		
		rgb_split = NULL;
		joined_rgb = split_more(split);
		if (joined_rgb)
			rgb_split = ft_split(joined_rgb, ',');
		split_error(rgb_split);
		col_code = check_colors_value(rgb_split);
		if(col_code == -1)
			error_colors_value(line, rgb_split, scene, joined_rgb);
		if (rgb_split)
			free_split_helper(rgb_split, scene, split[0][0]);
		free(joined_rgb);
	}
	free_split(split);
}
