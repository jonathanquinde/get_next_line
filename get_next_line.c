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

void	ft_strappend(char **str, char *value)
{
	size_t	len_new;
	size_t	len_str;
	char	*new_str;

	if (*value == '\0')
		return ;
	else if (**str == '\0')
	{
		*str = ft_strdup(value);
		return ;
	}
	len_str = ft_strlen(*str);
	len_new = len_str + ft_strlen(value);
	new_str = malloc(len_new + 1);
	if (str == NULL)
	{
		free (*str);
		*str = NULL;
		return ;
	}
	ft_strcpy(new_str, *str);
	ft_strcpy(new_str + len_str, value);
	free (*str);
	*str = new_str;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	if (len == 0)
		return (ft_strdup(""));
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	ft_strtruncate_until(char **str, size_t index)
{
	char	*new_str;

	new_str = ft_strdup(*str + index);
	free (*str);
	*str = new_str;
}

int read_file_until_nl_eof(int fd, char **buffer)
{
	char		buffer_read[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (*buffer == NULL)
		*buffer = ft_strdup("");
	if (ft_strcontains_ch(*buffer, '\n'))
		return (READ_NL); 
	while (1)
	{
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (READ_ERROR);
		else if (bytes_read == 0)
			return (READ_EOF);
		buffer_read[bytes_read] = '\0';
		ft_strappend(buffer, buffer_read);
		if (*buffer == NULL)
			return (READ_ERROR);
		if (ft_strcontains_ch(buffer_read, '\n'))
			return (READ_NL);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	size_t		len_line;
	int			read_status;

	read_status = read_file_until_nl_eof(fd, &buffer);
	if (read_status == READ_NL)
	{
		len_line = ft_strlenuntil(buffer, '\n') + 1;
		line = ft_substr(buffer, 0, len_line);
		if (line != NULL)
		{
			free (buffer);
			buffer = NULL;
			return (line);
		}
		ft_strtruncate_until(&buffer, len_line);
		if (buffer == NULL)
		{
			free (line);
			free (buffer);
			buffer = NULL;
			return (line);
		}
	}
	else if (read_status == READ_EOF && buffer != NULL && *buffer != '\0')
		line = buffer;
	else
	{
		free (buffer);
		buffer = NULL;
		line = NULL;
	}
	return (line);
}
