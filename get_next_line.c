/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- <jquinde-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:04:29 by jquinde-          #+#    #+#             */
/*   Updated: 2025/10/15 16:09:08 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

void	ft_strappend(char **str, char *value)
{
	size_t	len_new;
	size_t	len_str;
	char	*new_str;

	if (value == NULL)
		return ;
	else if (*str == NULL)
	{
		*str = ft_strdup(value);
		return ;
	}
	len_str = ft_strlen(*str);
	len_new = len_str + ft_strlen(value);
	new_str = malloc(len_new + 1);
	if (new_str == NULL)
	{
		ft_strclean(str);
		return ;
	}
	ft_strcpy(new_str, *str);
	ft_strcpy(new_str + len_str, value);
	free (*str);
	*str = new_str;
}

void	extract_line_truncate_buffer(char **line, char **buffer)
{
	char	*ptr_nl;	
	char	*new_buffer;

	ptr_nl = ft_strchr(*buffer, '\n');
	if (ptr_nl[1] == '\0')
	{
		*line = *buffer;
		*buffer = NULL;
		return ;
	}
	*line = malloc(ptr_nl - *buffer + 2);
	if (*line == NULL)
	{
		ft_strclean(buffer);
		return ;
	}
	ft_strncpy(*line, *buffer, ptr_nl - *buffer + 1);
	new_buffer = ft_strdup(ptr_nl + 1);
	free (*buffer);
	*buffer = new_buffer;
	if (new_buffer == NULL)
		ft_strclean(line);
}

int	read_file_until_nl_eof(int fd, char **buffer)
{
	char	*buffer_read;
	ssize_t	bytes_read;

	if (*buffer != NULL && ft_strchr(*buffer, '\n'))
		return (READ_NL);
	buffer_read = malloc(BUFFER_SIZE + 1);
	if (buffer_read == NULL)
		return (READ_ERROR);
	while (1)
	{
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer_read), READ_ERROR);
		if (bytes_read == 0)
			return (free(buffer_read), READ_EOF);
		buffer_read[bytes_read] = '\0';
		ft_strappend(buffer, buffer_read);
		if (*buffer == NULL)
			return (free(buffer_read), READ_ERROR);
		if (ft_strchr(buffer_read, '\n'))
			return (free(buffer_read), READ_NL);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_status;

	line = NULL;
	read_status = read_file_until_nl_eof(fd, &buffer);
	if (read_status == READ_NL)
		extract_line_truncate_buffer(&line, &buffer);
	else if (read_status == READ_EOF)
	{
		line = buffer;
		buffer = NULL;
	}
	else if (read_status == READ_ERROR)
		ft_strclean(&buffer);
	return (line);
}
