/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- < jquinde-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:48:37 by jquinde-          #+#    #+#             */
/*   Updated: 2024/11/21 20:23:40 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clean_node(t_list **lst)
{
	t_list	*node_to_free;

	node_to_free = *lst;
	*lst = (*lst)->next;
	free (node_to_free);
}

t_list	*new_node(int fd)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->file.identifier = fd;
	new_node->file.line = malloc(1);
	if (new_node->file.line == NULL)
	{
		free (new_node);
		return (NULL);
	}
	*new_node->file.line = '\0';
	return (new_node);
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

	if (str == NULL)
		return (0);
	if (len == BYPASS)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;	
		}
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

	buffer_len = ft_strlen(*buffer);
	new_buffer = malloc(buffer_len + n_bytes + 1);
	if (new_buffer == NULL)
		return (1);
	i = 0;
	while (i < buffer_len)
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	while (i - buffer_len < n_bytes)
	{
		new_buffer[i] = read_buffer[i - buffer_len];
		i++;
	}
	new_buffer[i] = '\0';
	free (*buffer);
	*buffer = new_buffer;
	return (0);
}
