/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:54:03 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/24 17:12:35 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_color_path(char flag, t_scene *scene, char **split)
{
	free_split(split);
	get_next_line(-1);
	free_scene(scene);
	if (flag == 'F')
		write(2, "Errore doppio path per il colore dei floor\n", 44);
	if (flag == 'C')
		write(2, "Errore doppio path per il colore dei cieling\n", 46);
	exit(EXIT_FAILURE);
}

void	error_colors_value(char *line, char **rgb_split, t_scene *scene,
	char *joined)
{
	free(line);
	free(joined);
	free_split(rgb_split);
	get_next_line(-1);
	free_scene(scene);
	write(2, "Errore valore colori\n", 22);
	exit(EXIT_FAILURE);
}

void	error_spawn_player(char *line, t_scene *scene)
{
	free(line);
	get_next_line(-1);
	free_scene(scene);
	write(2, "Errore spawn player\n", 21);
	exit(EXIT_FAILURE);
}

int	is_config_id(char *id)
{
	if (!id)
		return (0);
	return (ft_strncmp(id, "NO", 3) == 0
		|| ft_strncmp(id, "SO", 3) == 0
		|| ft_strncmp(id, "WE", 3) == 0
		|| ft_strncmp(id, "EA", 3) == 0
		|| ft_strncmp(id, "F", 2) == 0
		|| ft_strncmp(id, "C", 2) == 0);
}
