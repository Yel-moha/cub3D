/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/02 16:51:13 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//da cancellare prima di pusciare
#include <stdio.h>

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void print_split(char **split)
{
	int i;

	i = 0;
	while (split && split[i])
	{
		printf("token[%d]: %s\n", i, split[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**split;
	const char	*map_path;

	map_path = "src/valid_minimal.cub";
	if (argc == 2)
		map_path = argv[1];
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("file vuoto o non leggibile: %s\n", map_path);
		close(fd);
		return (1);
	}
	printf("prima riga: %s", line);
	split = ft_split(line, ' ');
	print_split(split);
	free(line);
	free_split(split);
	close(fd);
	return (0);
}