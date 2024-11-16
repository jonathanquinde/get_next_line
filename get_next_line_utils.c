/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- < jquinde-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:48:37 by jquinde-          #+#    #+#             */
/*   Updated: 2024/11/16 23:01:10 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strncpy(char *dest, char *src, size_t n)
{
	while (n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = 0;
}

size_t	ft_strlen(const char *str)
{
	const char	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

int	is_newline(char *str, size_t len)
{
	size_t	i;

	if (len == BYPASS)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
		}
		str++;	
		return (0);
	}
	i = 0;
	while (i < len)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	join_and_free(char **buffer, char *read_buffer, size_t n_bytes)
{
	char	*new_buffer;
	size_t	buffer_len;
	size_t	i;

	i = 0;
	buffer_len = ft_strlen(*buffer);
	new_buffer = malloc(buffer_len + n_bytes + 1);
	if (new_buffer == NULL)
		return (1);
	while (i < buffer_len)
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	ft_strncpy(&new_buffer[i], read_buffer, n_bytes);
	free (*buffer);
	*buffer = new_buffer;
	return (0);
}
