/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:33 by shhidrob          #+#    #+#             */
/*   Updated: 2025/03/30 13:55:22 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*extract_line(char *buff)
{
	char	*nl;
	int	len;
	char	*line;
	int	i;

	nl = ft_strchr(buff, '\n');
	printf("%lld,\n", (long long)nl);
	len = nl - buff + 1;
	printf("%d,\n", len);
	line = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		line[i] = buff[i];
		i++;
	}
	ft_memmove(buff, nl + 1, BUFFER_SIZE - len + 1);
	return (line);
}


char *readbuff(int fd, char *buff)
{
    int 	rid;
    char	*storage;

    buff[0] = '\0';
    rid = read(fd, buff, BUFFER_SIZE);
    storage = NULL;
    while (rid > 0 && !ft_strchr(buff, '\n'))
    {
        if (rid > 0)
        {
            buff[rid] = '\0';
	    if (storage == NULL)
		    storage = ft_strdup(buff);
	    else 
            	storage = ft_strjoin(storage, buff);
        }
        rid = read(fd, buff, BUFFER_SIZE);
	if (BUFFER_SIZE == 0)
		return (storage);
    }
    if (rid == 0)
	    buff[0] = 0;
    return (buff);
}

char *get_next_line(int fd)
{
    static char buff[BUFFER_SIZE + 1] = {0}; //line
    int r; //result of read
    int eof; //end of file
	char	*storage;
	char	*line;

   	if(fd < 0 || BUFFER_SIZE <= 0)
       		return (NULL);
    // storage = malloc(sizeof(char) * (BUFFER_SIZE + 1)); //need space to allocate the number of BUFFER_SIZE is reading
    
   	if (buff[0] == 0 || !ft_strchr(buff, '\n'))
    		storage = readbuff(fd, buff);
	line = extract_line(buff);
	//storage = ft_strjoin(storage, buff);
   	storage = ft_strjoin(storage, line); //join the buffer with the storage
	free(line);
    	return (storage); //return the storage
}

int main(int argc, char **argv)
{
//    char *buff = ft_strdup("1234567890");
//    buff[0] = 0;
//    char *result = ft_strjoin(buff, ft_strdup(""));
//    printf("%s\n", result);
//    return (0);

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
	    printf("Line read from file:\n");
            printf("%s\n", line);
            free(line);
            line = get_next_line(fd);
        }
        close(fd);
	printf("File now closed\n");
    }
    return (0);
}
