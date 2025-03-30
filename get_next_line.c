/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:33 by shhidrob          #+#    #+#             */
/*   Updated: 2025/03/30 17:57:32 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*readbuff(int fd, char *buff)
{
	char	*storage;
	int		rid;

	storage = ft_strdup(buff);
	rid = read(fd, buff, BUFFER_SIZE);
	while (rid > 0 && !ft_strchr(buff, '\n'))
	{
		buff[rid] = '\0';
		storage = ft_strjoin(storage, buff);
		rid = read(fd, buff, BUFFER_SIZE);
	}
	if (rid <= 0)
	{
		buff[0] = 0;
		if (storage[0] == '\0')
			return (free(storage), NULL);
	}
	else
	{
		buff[rid] = '\0';
		storage = ft_strnjoin(storage, buff, ft_strchr(buff, '\n') - buff + 1);
		ft_memmove(buff, ft_strchr(buff, '\n') + 1,
				rid - (ft_strchr(buff, '\n') - buff));
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*storage;
	char		*line;

	storage = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(buff, '\n'))
		storage = readbuff(fd, buff);
	else
	{
		line = ft_strndup(buff, ft_strchr(buff, '\n') - buff + 1);
		ft_memmove(buff, ft_strchr(buff, '\n') + 1,
			       ft_strlen(buff) - (ft_strchr(buff, '\n') - buff));
	}
	return (storage);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc == 2)
    {
	printf("Opening file: %s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	    return (1);
	printf("File opened\n");
	line = get_next_line(fd);
	while (line)
	{
	    printf("%s", line);
	    free(line);
	    line = get_next_line(fd);
	}
	close(fd);
	printf("File now closed\n");
    }
    return (0);
}
