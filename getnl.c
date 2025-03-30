/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhidrob <shhidrob@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:33 by shhidrob          #+#    #+#             */
/*   Updated: 2025/03/30 15:29:04 by shhidrob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char *readbuff(int fd, char *buff)
{
    int 	rid;
    char	*storage;

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
		{
			free (storage);
			return (NULL);
		}
	}
    else 
	{
		buff[rid] = '\0';
		storage = ft_strnjoin(storage, buff, ft_strchr(buff, '\n') - buff + 1);
		ft_memmove(buff, ft_strchr(buff, '\n') + 1 , rid - (ft_strchr(buff, '\n') - buff));
	}
	 
    return (storage);
}

char *get_next_line(int fd)
{
    static char buff[BUFFER_SIZE + 1]; //line
    //int r; //result of read
    //int eof; //end of file
	char	*storage;
	//char	*line;

   	if(fd < 0 || BUFFER_SIZE <= 0)
       		return (NULL);
    // storage = malloc(sizeof(char) * (BUFFER_SIZE + 1)); //need space to allocate the number of BUFFER_SIZE is reading
    
   	if (!ft_strchr(buff, '\n'))
    		storage = readbuff(fd, buff);
	else
	{
	
		ft_strndup(buff, ft_strchr(buff, '\n') - buff + 1); 
		ft_memmove(buff, ft_strchr(buff, '\n') + 1, ft_strlen(buff) - (ft_strchr(buff, '\n') - buff));
	}
	//line = extract_line(buff);
	//storage = ft_strjoin(storage, buff);
   	//storage = ft_strjoin(storage, line); //join the buffer with the storage
	//free(line);
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
	    printf("%s", line);
	    free(line);
	    line = get_next_line(fd);
	}
	close(fd);
	printf("File now closed\n");
    }
    return (0);
}
