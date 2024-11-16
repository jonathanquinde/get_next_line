/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- < jquinde-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:56:04 by jquinde-          #+#    #+#             */
/*   Updated: 2024/10/15 12:56:04 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		read_file(int fd, char	**buffer);
char	*get_and_trim(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			read_status;
	char		*result;

	if (buffer == NULL)
	{
		buffer = malloc(1);
		if (buffer == NULL)
			return (NULL);
		*buffer = 0;
	}
	read_status = READ_SUCCESS;
	//strlen innecesario
	if (!(is_newline(buffer, ft_strlen(buffer))))
		read_status = read_file(fd, &buffer);
	if (read_status == READ_SUCCESS)
	{
		result = get_and_trim(buffer);
		if (result != NULL)
			return (result);
	}
	free (buffer);
	buffer = NULL;
	return (NULL);
}

int	read_file(int fd, char **buffer)
{
	char	*read_buffer;
	int		n_bytes;

	read_buffer = malloc(BUFFER_SIZE);
	if (read_buffer == NULL)
		return (READ_ERROR);
	n_bytes = read(fd, read_buffer, BUFFER_SIZE);
	while (n_bytes > 0)
	{
		if (join_and_free(buffer, read_buffer, n_bytes))
		{
			free (read_buffer);
			return (READ_ERROR);
		}
		if (is_newline(read_buffer, n_bytes))
		{
			free(read_buffer);
			return (READ_SUCCESS);
		}
		n_bytes = read(fd, read_buffer, BUFFER_SIZE);
	}
	free(read_buffer);
	if (n_bytes == -1 || **buffer == 0)
		return (READ_ERROR);
	return (READ_SUCCESS);
}

char	*get_and_trim(char *buffer)
{
	char	*result;
	size_t	i;
	size_t	len;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	result = malloc(i + 1 + (buffer[i] == '\n'));
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, buffer, i + (buffer[i] == '\n'));
	len = ft_strlen(buffer + i + (buffer[i] == '\n'));
	ft_strncpy(buffer, buffer + i + (buffer[i] == '\n'), len);
	return (result);
}
