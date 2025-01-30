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

#include "get_next_line_bonus.h"

int		read_file(int fd, char	**buffer);
char	*get_and_trim(char *buffer);
char	*process_file(int fd, char **buffer);
t_list	*search_node(t_list *lst, int fd);

char    *get_next_line(int fd)
{
    static t_list   *start;
    char            *result;
	t_list			*node_to_process;

	node_to_process = search_node(start, fd);
	if (node_to_process == NULL)
	{
		node_to_process = new_node(fd);
		if (node_to_process == NULL)
			return (NULL);
		result = process_file(fd, &node_to_process->file.line);
		if (result == NULL)
			free (node_to_process);
		else
		{
			node_to_process->next = start;
			start = node_to_process;
		}
		return (result);
	}
	result = process_file(fd, &node_to_process->file.line);
	if (result == NULL)
		clean_node(&node_to_process);
	return (result);
}

t_list	*search_node(t_list *lst, int fd)
{
	while (lst != NULL)
	{
		if (lst->file.identifier == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	*process_file(int fd, char **buffer)
{
	int			read_status;
	char		*result;

	read_status = READ_SUCCESS;
	if (!(is_newline(*buffer, BYPASS)))
		read_status = read_file(fd, buffer);
	if (read_status == READ_SUCCESS || read_status == READ_LAST_LINE)
	{
		result = get_and_trim(*buffer);
		if (read_status == READ_LAST_LINE)
		{
			free (*buffer);
			*buffer = NULL;
		}
		if (result != NULL)
			return (result);
	}
	free (*buffer);
	*buffer = NULL;
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
	if (n_bytes == -1 || *buffer == 0 || **buffer == 0)
		return (READ_ERROR);
	return (READ_LAST_LINE);
}

char	*get_and_trim(char *buffer)
{
	char	*start_buffer;
	char	*result;
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	result = malloc(i + (buffer[i] == '\n') + 1);
	if (result == NULL)
		return (NULL);	
	start_buffer = buffer;
	while (*buffer != '\n' && *buffer)
		*result++ = *buffer++;
	if (*buffer == '\n')
		*result++ = *buffer++;
	*result = '\0';
	while (*buffer != '\0')
		*start_buffer++ = *buffer++;
	*start_buffer = '\0';
	return (result - i - (result[-1] == '\n'));
}
