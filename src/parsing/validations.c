/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:16:54 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/02 17:41:52 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_flags(t_scene *scene, char *flag)
{
	char	*joined;

	joined = ft_strjoin(scene->flag, flag);
	if (!joined)
		return ;
	free(scene->flag);
	scene->flag = joined;
	scene->counter++;
}

void	fill_colors(char **line, t_scene *scene, char f_or_c)
{
	if (!line || !line[0] || !line[1] || !line[2])
		return ;
	if (f_or_c == 'F')
	{
		if (ft_strchr(scene->flag, 'F'))
			double_color_path('F', scene, line);
		scene->floor.r = ft_atoi(line[0]);
		scene->floor.g = ft_atoi(line[1]);
		scene->floor.b = ft_atoi(line[2]);
		scene->floor.value = (scene->floor.r << 16)
			| (scene->floor.g << 8) | scene->floor.b;
		update_flags(scene, "F");
	}
	else if (f_or_c == 'C')
	{
		if (ft_strchr(scene->flag, 'C'))
			double_color_path('C', scene, line);
		scene->ceiling.r = ft_atoi(line[0]);
		scene->ceiling.g = ft_atoi(line[1]);
		scene->ceiling.b = ft_atoi(line[2]);
		scene->ceiling.value = (scene->ceiling.r << 16)
			| (scene->ceiling.g << 8) | scene->ceiling.b;
		update_flags(scene, "C");
	}
}

int	check_colors_value(char **rgb_split, char **split)
{
	int	i;
	int	j;

	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2])
		return (-1);
	i = 0;
	while (rgb_split[i])
	{
		j = 0;
		while (rgb_split[i][j] && ft_atoi(rgb_split[i]) >= 0)
		{
			if ((!ft_isdigit(rgb_split[i][j]) && rgb_split[i][j] != '\n') ||
				ft_atoi(&rgb_split[i][j]) > 255)
			{
				free_split(split);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
