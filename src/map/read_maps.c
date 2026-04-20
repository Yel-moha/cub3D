/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:24:22 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/04 11:30:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*append_buffer(char *buffer, char *temp)
{
	char	*joined;

	if (!buffer)
		joined = ft_strjoin("", temp);
	else
		joined = ft_strjoin(buffer, temp);
	free(buffer);
	return (joined);
}

static void	*read_line(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = append_buffer(buffer, temp);
		if (!buffer)
			return (free(temp), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	if (bytes_read < 0 || !buffer || (bytes_read == 0 && !buffer[0]))
		return (free(buffer), NULL);
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (!*buffer || !**buffer)
		return (free(*buffer), *buffer = NULL, NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + 1);
	temp = ft_strdup(&(*buffer)[i + 1]);
	free(*buffer);
	if (temp && *temp)
		*buffer = temp;
	else
		free(temp), *buffer = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	return (extract_line(&buffer));
}