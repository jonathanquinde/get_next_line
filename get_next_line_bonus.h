/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- < jquinde-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:05:23 by jquinde-          #+#    #+#             */
/*   Updated: 2024/10/14 13:05:23 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H 
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define BYPASS 0
# define READ_ERROR 1
# define READ_SUCCESS 2
# define READ_LAST_LINE 3

char	*get_next_line(int fd);
int		is_newline(char *read_buffer, size_t len);
size_t	ft_strlen(const char *str);
int     join_and_free(char **buffer, char *read_buffer, size_t n_bytes);
#endif