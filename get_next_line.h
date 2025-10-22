/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquinde- <jquinde-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:42:53 by jquinde-          #+#    #+#             */
/*   Updated: 2025/10/13 20:45:03 by jquinde-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define READ_ERROR -1
# define READ_NL 1
# define READ_EOF 0

char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlen(const char *str);
void	ft_strclean(char **str);
char	*get_next_line(int fd);

#endif
