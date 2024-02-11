/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:51:17 by lcuellar          #+#    #+#             */
/*   Updated: 2024/02/03 18:27:35 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_null(char **ptr)
//Free the memory and set the pointer to NULL
{
	if (*ptr != NULL)
	{
		free(*ptr);
		ptr = NULL;
	}
}

char	*join_line(int new_line_position, char **buffer)
// Return the line and update the buffer with the rest of the string
{
	char	*line;
	char	*aux;

	aux = NULL;
	if (new_line_position <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		line = *buffer;
		*buffer = NULL;
		return (line);
	}
	aux = ft_substr(*buffer, new_line_position, BUFFER_SIZE);
	line = *buffer;
	line[new_line_position] = 0;
	*buffer = aux;
	return (line);
}

char	*read_line(int fd, char **buffer, char *line)
// Read the file descriptor until it encounters a newline or EOF.
{
	ssize_t	nbytes;
	char	*aux;
	char	*new_line;

	nbytes = 0;
	aux = NULL;
	new_line = ft_strchr(*buffer, '\n');
	while (!new_line)
	{
		nbytes = read(fd, line, BUFFER_SIZE);
		if (nbytes <= 0)
			return (join_line(nbytes, buffer));
		line[nbytes] = 0;
		aux = ft_strjoin(*buffer, line);
		free_null(buffer);
		*buffer = aux;
		new_line = ft_strchr(*buffer, '\n');
	}
	return (join_line(new_line - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
// Read the file descriptor and return the line
{
	static char	*buffer[MAX_BUFF + 1];
	char		*line;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_BUFF)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line == NULL)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	res = read_line(fd, &buffer[fd], line);
	free_null(&line);
	return (res);
}
