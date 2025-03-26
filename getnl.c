/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:33 by shhidrob          #+#    #+#             */
/*   Updated: 2025/03/26 20:44:32 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *buff)
{
	char	*nl;
	int	len;
	char	*line;
	int	i;

	nl = ft_strchr(buff, '\n');
	len = nl - buff + 1;
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

    buffer[0] = '\0';
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
    }
    if (rid == 0)
	    buff[0] = 0;
    return (storage);
}

'0'
'\0' == 0

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
   	storage = ft_strjoin(storage, line); //join the buffer with the storage
	free(line);
    	return (storage); //return the storage
}

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            return (1);
        line = get_next_line(fd);
        while (line)
        {
            printf("%s\n", line);
            free(line);
            line = get_next_line(fd);
        }
        close(fd);
    }
    return (0);
}
