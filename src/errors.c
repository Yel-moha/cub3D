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

void double_color_path(char flag, t_scene *scene, char **split)
{
	free_split(split);
	get_next_line(-1);
	free_scene(scene);
	write(1, "double path\n", ft_strlen("double path") + 1);
	if(flag == 'F')
		write(2, "Errore doppio path per il colore dei floor\n", \
			ft_strlen("Errore doppio path per il colore dei floor") + 1);
	if(flag == 'C')
		write(2, "Errore doppio path per il colore dei cieling\n", \
			ft_strlen("Errore doppio path per il colore dei cieling") + 1);
	exit(EXIT_FAILURE);
}

void error_colors_value(char *line, char **rgb_split, t_scene *scene, char *joined)
{
	free(line);
	free(joined);
	free_split(rgb_split);
	get_next_line(-1);
	free_scene(scene);
	write(2, "Errore valore colori\n", \
			ft_strlen("Errore valore colori\n") + 1);
	exit(EXIT_FAILURE);
}
void error_spawn_player(char *line, t_scene *scene)
{
	free(line);
	get_next_line(-1);
	free_scene(scene);
	write(2, "Errore spawn player\n", \
			ft_strlen("Errore spawn player\n") + 1);
	exit(EXIT_FAILURE);
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

void	split_error(char **split)
{
	if (!split || !split[0])
	{
		free_split(split);
		exit(EXIT_FAILURE);
	}
	return ;
}

static int	is_config_id(char *id)
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

void	error_extra_line_map(char *line, t_scene *scene)
{
	char	**split;

	if (!line || !scene)
		return ;
	if (is_blank_line(line))
		return ;
	split = ft_split(line, ' ');
	if (!split || !split[0])
	{
		free_split(split);
		return ;
	}
	if (is_config_id(split[0]) || is_map_line(line))
	{
		free_split(split);
		return ;
	}
	free_split(split);
	free(line);
	get_next_line(-1);
	free_scene(scene);
	write(2, "Error\nlinea fuori contesto nella mappa\n", 39);
	exit(EXIT_FAILURE);
}
