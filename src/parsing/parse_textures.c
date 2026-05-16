/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	split_len(char **split)
{
	int	len;

	len = 0;
	while (split && split[len])
		len++;
	return (len);
}

static int	is_texture_id(const char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "NO", 3) == 0
		|| ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0
		|| ft_strncmp(id, "EA", 3) == 0);
}

static int	parse_texture_tokens(char **split, char *line, t_scene *scene,
	int fd)
{
	int	len;
	int	i;

	len = split_len(split);
	if (len < 2)
	{
		line_errors(line, fd);
		return (0);
	}
	if (len > 2)
		check_extra_chars_textures(scene, line, split);
	i = 1;
	while (i < len && split[i] && split[i][0] == '\0')
		i++;
	if (i >= len || !split[i] || split[i][0] == '\0')
		return (0);
	fill_direction_fixed(split, scene, i);
	return (1);
}

void	parse_textures(char *line, t_scene *scene, int fd)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !is_texture_id(split[0]))
	{
		free_split(split);
		return ;
	}
	if (!parse_texture_tokens(split, line, scene, fd))
	{
		free_split(split);
		return ;
	}
	free_split(split);
}
