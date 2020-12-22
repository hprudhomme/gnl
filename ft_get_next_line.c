#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (s == NULL)
		return (NULL);
	subs = ft_strnew(len);
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}

void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = src[i];
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		size += 1;
	}
	return (size);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		strlen;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = ft_strnew(strlen);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
		ft_memdel((void**)as);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

static int  ft_breakline(char **src, char **line)
{
    int len;
    char *tmp;

    len = 0;
    while ((*src)[len] != '\n' && (*src)[len] != '\0')
        len++;
    if ((*src)[len] == '\n')
    {
        *line = ft_substr(*src, 0, len);
        tmp = ft_strdup(&((*src)[len + 1]));
        free(*src);
        *src = tmp;
        if ((*src)[0] == '\0')
			ft_strdel(src);
    }
    else
	{	
		*line = ft_strdup(*src);
		ft_strdel(src);
	}
	return (1);
}

static int  ft_verif(char **src, char **line, int ret, int fd)
{
    if (ret < 0)
        return (-1);
    else if (ret == 0 && src[fd] == NULL)
        return (0);
    else
        return (ft_breakline(&src[fd], line));
}

int     get_next_line(int fd, char **line)
{
    int ret;
    static char *src[4096];
    char        buf[BUFFER_SIZE + 1];
    char        *tmp;

    if (fd < 0 || line == NULL)
        return (-1);
    while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[ret] = '\0';
        if (src[fd] == NULL)
            src[fd] = ft_strdup(buf);
        else
        {
            tmp = ft_strjoin(src[fd], buf);
            free(src[fd]);
            src[fd] = tmp;
        }
        if (ft_strchr(src[fd], '\n'))
            break ;
    }
    return(ft_verif(src, line, ret, fd));
}

int   main(int ac, char **av)
{
  char  *line;
  int   fd1;
  int   fd2;
  int   fd3;

  fd1 = open(av[1], O_RDONLY);
  fd2 = open(av[2], O_RDONLY);
  fd3 = open(av[3], O_RDONLY);
  get_next_line(fd1, &line);
  printf("%s\n", line);

  printf("---------------------------------------------------------------------------------------------------------------------------------\n");

  get_next_line(fd1, &line);
  printf("%s\n", line);
}