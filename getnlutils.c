#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *new_str;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return (NULL);
    new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        new_str[i + j] = s2[j]; //i + j to start from the end of s1 - maybe i + 1 to start from the end of s1 + '\0'
        j++;
    }
    new_str[i + j] = '\0'; // it could be new_str[j + 1] = '\0';
    free(s1); //free s1 because we are going to return new_str, free 2nd parameter in get_next_line
    return (new_str);
}

/*char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *new_str;
    size_t i;

    if (!s)
        return (NULL);
    new_str = malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < len && s[start + i])
    {
        new_str[i] = s[start + i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}*/

char *ft_strchr(const char *s, int c)
{
    size_t i;

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
// 	while (rid > 0 && !ft_strchr(buffer, '\n'))