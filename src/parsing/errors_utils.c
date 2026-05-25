/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	line_errors(char *line, int fd)
{
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	if (!line)
	{
		write(2, "file vuoto o non leggibile:\n", 29);
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
}
