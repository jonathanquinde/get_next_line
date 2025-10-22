/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- <jquinde-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:43:51 by jquinde-          #+#    #+#             */
/*   Updated: 2025/10/15 15:55:58 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strclean(char **str)
{
	free(*str);
	*str = NULL;
}

size_t	ft_strlen(const char *str)
{
	const char	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
int	ft_strcontains_ch(char	*str, char ch)
{
	while (*str)
	{
		if (*str == ch)
			return (1);
		str++;
	}
	return (0);
}

ssize_t	ft_strlenuntil(char *str, char ch)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == ch)
			return (len);
		len++;
	}
	return (-1);
}
 * */

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *) s);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strcpy(new_str, str);
	return (new_str);
}
