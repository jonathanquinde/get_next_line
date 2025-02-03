/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- < jquinde-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:48:37 by jquinde-          #+#    #+#             */
/*   Updated: 2025/02/03 11:49:38 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strncpy(char *dest, char *src, size_t n)
{
	if (n == BYPASS)
	{
		while (*src)
		{
			*dest = *src;
			dest++;
			src++;
		}
		*dest = 0;
		return ;
	}
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

int has_newline(t_list *buffer)
{
	size_t i;

	while (buffer != NULL)
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (((char *) buffer->content)[i] == '\n')
				return (1);
			i++;
		}
		buffer = buffer->next;
	}
	return (0);
}

t_list *ft_lstnew(void *content)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->next = NULL;
	node->content = content;
	return (node);
}

void ft_lstaddfront(t_list **head, t_list *node)
{
	node->next = *head;
	*head = node;
}

size_t ft_lstsize(t_list *list)
{
	size_t size;

	size = 0;
	while (list != NULL)
	{
		size++;
		list = list->next;
	}
	return (size);	
}