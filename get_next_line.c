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

int		read_file(int fd, t_list **buffer);
char	*get_and_trim(t_list *buffer);

char	*get_next_line(int fd)
{
	t_list      *buffer;
	int			read_status;
	char		*result;

	read_status = READ_SUCCESS;
	if (!(is_newline(buffer)))
		read_status = read_file(fd, &buffer);
	if (read_status == READ_SUCCESS || read_status == READ_LAST_LINE)
	{
		result = get_and_trim(buffer);
		if (read_status == READ_LAST_LINE)
		{
			free (buffer);
			buffer = NULL;
		}
		if (result != NULL)
			return (result);
	}
	free (buffer);
	buffer = NULL;
	return (NULL);
}

//En caso de error de malloc se deberia contemplar el fallo(si uno de los dos no falla tinene que ser liberado)
int	read_file(int fd, t_list **buffer)
{
	t_list *new_node;
	int		n_bytes;

	new_node = ft_lstnew(malloc(BUFFER_SIZE));	
	if (new_node == NULL || new_node->content == NULL)
		return (READ_ERROR);
	n_bytes = read(fd, new_node->content, BUFFER_SIZE);
	while (n_bytes > 0)
	{
		ft_lstaddfront(buffer, new_node);
		if (is_newline(new_node))
			return (READ_SUCCESS);
		new_node = ft_lstnew(malloc(BUFFER_SIZE));	
		if (new_node == NULL || new_node->content == NULL)
			return (READ_ERROR);
		n_bytes = read(fd, new_node->content, BUFFER_SIZE);
	}
	free (new_node->content);
	free (new_node);
	if (n_bytes == -1 || *buffer == NULL)
		return (READ_ERROR);
	return (READ_LAST_LINE);
}

char	*get_and_trim(t_list *buffer)
{
	static size_t	leftover_size = BUFFER_SIZE;
	char	*result;
	size_t	i;
	size_t 	middle_size;
	size_t	end_size;

	end_size = (BUFFER_SIZE - leftover_size);
	if (buffer->next != NULL && buffer->next->next != NULL)
		middle_size = ((ft_lstsize(buffer) - 2) * BUFFER_SIZE);
	else
		middle_size = 0;
	i = 0;
	while (((char *)buffer->content)[i] != '\n' && ((char *)buffer->content)[i])
		i++;
	result = malloc(end_size + middle_size + i + (((char *)buffer->content)[i] == '\n') + 1);
	if (result == NULL)
		return (NULL);	
	
}

