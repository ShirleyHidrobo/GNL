#include "get_next_line.h"

char readbuff(int fd, char *storage)
{
    int i,
    char *buffer;

    i = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (ft_free(&storage));
    while(i > 0 && !ft_strchr(buffer, '\n'))
    {
        i = read(fd, buffer, BUFFER_SIZE);
        if (i > 0)
        {
            buffer[i] = '\0';
            storage = ft_strjoin(storage, buffer);
        }
    }
    free(buffer);//free the buffer
    if (i == -1)
        return (ft_free(&storage));
    return (storage);}



char readbuff(int fd, char *storage)
{
    int rid;
    char *buffer;

    rid = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (ft_free(&storage));
    buffer[0] = '\0';
    while (rid > 0 && !ft_strchr(buffer, '\n'))
    {
        rid = read(fd, buffer, BUFFER_SIZE);
        if (rid > 0)
        {
            buffer[rid] = '\0';
            storage = ft_strjoin(storage, buffer);
        }
    }
    free(buffer);
    if (rid == -1)
        return (ft_free(&storage));
    return (storage);
}


/*size_t read(int fd, char *buf, size_t BUFFER_SIZE)
{
    size_t i;
    char c;

    i = 0;
    while (i < BUFFER_SIZE)
    {
        if (read(fd, &c, 1) == 0)
            return (i);
        buf[i] = c;
        i++;
    }
    return (i);
}*/

size_t read(int fd, char *buff, size_t BUFFER_SIZE)
{
    size_t i;
    char c;

    i = 0;
    while( i < BUFFER_SIZE)
    {
        if (read(fd, &c, 1) == 0)
            return (i); //if read returns 0 then we have reached the end of the file
        buff[i] = c; //store the character in the buffer - no necesito inicializar c? o ya se inicializa con el valor de la lectura? &c es la direccion de c
        if (buff[i] == '\n')
            return (i);
        i++;
    }
    return (i); //return the number of characters read
}

char *get_next_line(int fd)
{
    static char *storage; //line
    char *buff; //buff
    int r; //result of read
    int eof; //end of file

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    storage = malloc(sizeof(char) * (BUFFER_SIZE + 1)); //need space to allocate whatever is in the buffer + 1 for the null terminator
    if (!storage)
        return (NULL); //if malloc fails return NULL
    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1)); //need space to allocate the number of BUFFER_SIZE is reading
    if (!buf)
        return (ft_free(&storage)); // if malloc fails free storage because there is no space to check what is read therefore nothing to be saved in storage 
    r = read(fd, buff, BUFFER_SIZE); // read stuff into buffer
    if (r == 0 || r == -1)
        return (ft_free(&storage)); //nothing has been read, free whatever was in storage
    if (r != BUFFER_SIZE)
        eof = 1; //then we have reached eof at some point inside the buffer
    buff[r] = '\0'; //null terminate the buffer - pero en strjoin ya se pone el null, y sino no seria r +1? osea el ultimo caracter +1 xq sino estaria reemplazando al ultimo caracter
    storage = ft_strjoin(storage, buff); //join the buffer with the storage
    free(buff); //free the buffer
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