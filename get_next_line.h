/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:38:21 by shhidrob          #+#    #+#             */
/*   Updated: 2025/03/30 15:26:26 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	*get_next_line(int fd);
char	*readbuff(int fd, char *buff);
char	*extract_line(char *buff);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(char *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
char	*ft_strdup(char *src);
char *ft_strnjoin(char *s1, char *s2,size_t n);
char	*ft_strchr(char *s, int c);

#endif
