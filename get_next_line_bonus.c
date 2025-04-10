/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:33 by shhidrob          #+#    #+#             */
/*   Updated: 2025/04/02 17:48:06 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"
// #include "get_next_line_utils.c"

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

char	*readbuff(int fd, char *buff, char *storage)
{
	int		rid;

	rid = read(fd, buff, BUFFER_SIZE);
	if (rid >= 0)
		buff[rid] = '\0';
	while (rid > 0 && !ft_strchr(buff, '\n'))
	{
		storage = ft_strjoin(storage, buff);
		rid = read(fd, buff, BUFFER_SIZE);
		if (rid >= 0)
			buff[rid] = '\0';
	}
	if (rid < 0 || (rid == 0 && storage[0] == '\0'))
		return (free(storage), NULL);
	else if (rid > 0)
	{
		storage = ft_strnjoin(storage, buff, ft_strchr(buff, '\n') - buff + 1);
		ft_memmove(buff, ft_strchr(buff, '\n') + 1,
			rid - (ft_strchr(buff, '\n') - buff));
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	storage = ft_strdup(buff[fd]);
	if (!ft_strchr(buff[fd], '\n'))
		storage = readbuff(fd, buff[fd], storage);
	else
	{
		ft_memmove(buff[fd], ft_strchr(buff[fd], '\n') + 1,
			ft_strlen(buff[fd]) - (ft_strchr(buff[fd], '\n') - buff[fd]));
		storage[ft_strlen(storage) - ft_strlen
			(ft_strchr(storage, '\n')) + 1] = 0;
	}
	return (storage);
}

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (argc == 2)
//     {
// 	printf("Opening file: %s\n", argv[1]);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	    return (1);
// 	printf("File opened\n");
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 	    printf("%s", line);
// 	    free(line);
// 	    line = get_next_line(fd);
// 	}
// 	close(fd);
// 	printf("File now closed\n");
//     }
//     return (0);
// }

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

// 	fd = open("42_with_nl", O_RDONLY);
// 	if (fd == -1)
// 	    return (1);
// 	printf("File opened\n");
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 	    printf("%s", line);
// 	    free(line);
// 	    line = get_next_line(fd);
// 	}
// 	close(fd);
// 	printf("File now closed\n");
//     return (0);
// }

// int main(void)
// {
// 	char	*line;

// 	line = get_next_line(0);
// 	while (line)
// 	{
// 	    printf("%s", line);
// 	    free(line);
// 	    line = get_next_line(0);
// 	}
// 	return (0);
// }
