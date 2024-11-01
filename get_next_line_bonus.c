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

int		read_file(int fd, char	**buffer);
char	*get_linex(char *buffer);
char	*trim_read_line(char *buffer);

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
	read_status = 0;
	if (!(is_newline(buffer, ft_strlen(buffer))))
		read_status = read_file(fd, &buffer);
	if (read_status == 2)
		return (NULL);
	result = get_linex(buffer);
	if (read_status == 0)
	{
		buffer = trim_read_line(buffer);
		return (result);
	}
	*buffer = 0;
	return (result);
}

int	read_file(int fd, char **buffer)
{
	char	*read_buffer;
	int		n_bytes;

	read_buffer = malloc(BUFFER_SIZE);
	if (read_buffer == NULL)
		return (2);
	n_bytes = read(fd, read_buffer, BUFFER_SIZE);
	while (n_bytes > 0)
	{
		*buffer = join_and_free(*buffer, read_buffer, n_bytes);
		if (is_newline(read_buffer, n_bytes))
		{
			free(read_buffer);
			return (0);
		}
		n_bytes = read(fd, read_buffer, BUFFER_SIZE);
	}
	free(read_buffer);
	if (n_bytes == 0 && **buffer != 0)
		return (1);
	free (*buffer);
	*buffer = NULL;
	return (2);
}

char	*get_linex(char *buffer)
{
	char	*result;
	size_t	len;

	if (buffer == NULL)
		return (NULL);
	len = 0;
	while (buffer[len] != '\n' && buffer[len])
		len++;
	if (buffer[len] == 0)
	{
		result = malloc(len + 1);
		ft_strncpy(result, buffer, len);
		return (result);
	}
	result = malloc(len + 2);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, buffer, len + 1);
	return (result);
}

char	*trim_read_line(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	len;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (!buffer[i])
		return (buffer);
	len = ft_strlen(&buffer[i + 1]);
	new_buffer = malloc(len + 1);
	ft_strncpy(new_buffer, &buffer[i + 1], len);
	free (buffer);
	return (new_buffer);
}