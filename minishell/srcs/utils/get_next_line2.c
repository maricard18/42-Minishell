#include "minishell.h"

int ft_len2(char *str)
{
    int i = 0;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int ft_strchar(char *str, char c)
{
    int i = 0;

    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char *ft_strjoin2(char *s1, char *s2)
{
    char *s3;
    int i = 0;
    int a = 0;

    if (!s1)
    {
        s1 = malloc(sizeof(char) * 1);
        s1[i] = '\0';
    }
    s3 = malloc(sizeof(char) * (ft_len2(s1) + ft_len2(s2) + 1));
    while (s1[i])
    {
        s3[i] = s1[i];
        i++;
    }
    while (s2[a])
    {
        s3[i] = s2[a];
        i++;
        a++;
    }
    s3[i] = '\0';
    free(s1);
    return (s3);
}

char *ft_remove(char *str)
{
    char *line;
    int i = 0;
    int a = 0;

    if (!str)
        return (NULL);
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\0')
    {
        free(str);
        return (NULL);
    }
    line = malloc(sizeof(char) * (ft_len2(str) - i + 1));
    i++;
    while (str[i])
    {
        line[a] = str[i];
        i++;
        a++;
    }
    line[a] = '\0';
    free(str);
    return (line);
}

char *ft_write(char *str)
{
    char *line;
    int   i = 0;

    if (!str[i])
        return (NULL);
    while (str[i] && str[i] != '\n')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    // if (str[i] == '\n')
    // {
    //     line[i] = str[i];
    //     i++;
    // }
    line[i] = '\0';
    return (line);
}

char *ft_read(int fd, char *str)
{
    char *buf;
    int bytes = 1;

    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    while (bytes != 0 && ft_strchar(buf, '\n') == 0)
    {
        bytes = read(fd, buf, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[bytes] = '\0';
        str = ft_strjoin2(str, buf);
    }
    free(buf);
    return (str);
}

char *get_next_line2(int fd)
{
    static char *read;
    char *line;

    if (fd < 0 || BUFFER_SIZE < 0)
    {
        return (NULL);
    }
    read = ft_read(fd, read);
    if (!read)
        return (NULL);
    line = ft_write(read);
    read = ft_remove(read);
    return (line);
}

// int main()
// {
//     int	i;
// 	int	fd;
// 	char *line;

// 	i = 0;
// 	fd = open("teste.txt", O_RDONLY); 
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("Linha %i: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }