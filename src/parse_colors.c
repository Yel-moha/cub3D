/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:13:26 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 18:31:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	parse_textures(char *line, t_scene *scene, int fd)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0])
		line_errors(line, fd);
	fill_direction(split, scene);
	free_split(split);
}