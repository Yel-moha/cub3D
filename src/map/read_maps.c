/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:24:22 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/02 16:43:03 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, temp);
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
	if (!(*buffer) || !(*buffer)[0])
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + 1);
	if ((*buffer)[i] == '\n')
		temp = ft_strdup(&(*buffer)[i + 1]);
	else
		temp = ft_strdup("");
	free(*buffer);
	*buffer = temp;
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

/*
static char **read_map(void)
{
    int         fd;
    char        **file;
    char        *line;
    const char  *map_path;
    int         i;

    i = 0;
    map_path = "src/valid_minimal.cub";
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }
    printf("\n\nContenuto completo di %s:\n", map_path);
    file[i] = get_next_line(fd);
    while (line)
    {
        i++;
        //printf("%s", line);
        //free(line);
        //line = get_next_line(fd);
        file[i] = get_next_line(fd);
    }
    close(fd);
    return (file);
}

static void split_matrix(char **matrix)
{
    char **line;
    int i = 0;

    line = ft_split(matrix[0], " ");
    while(line)
    {
        printf("la prima linea del test e questa: %s\n", line[i]);
        i++;
    }
}
*/