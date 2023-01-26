#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	char	*s;

	i = 0;
	k = 0;
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		if (i < ft_strlen(s1))
			s[i] = s1[i];
		else
			s[i] = s2[k++];
		i++;
	}
	s[i] = 0;
	return (s);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((sizeof(char) * (ft_strlen(s) + 1)));
	if (!dup)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c %= 256;
	while (1)
	{
		if (s[i] == c)
			return (i);
		if (s[i] == 0)
			return (0);
		i++;
	}
}

static char	*read_func(int fd, char *line)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_size, i = 0;
	while (1)
	{
		printf ("%drd loop\n", ++i);
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			// printf ("lineeee === '%s'\n", line);
			free (line);
			return (NULL);
		}
		buf[read_size] = 0;
		if (!line)
		{
			line = ft_strdup (buf);
			printf ("dup arac line: '%s'\n\n", line);
		}
		else
		{
			printf ("join arac line: '%s'\n\n", line);
			line = ft_strjoin (line, buf);
		}
		if (ft_strchr(line, '\n') || read_size == 0)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;
	char		*tmp;

	if (fd < 0)
		return (NULL);
	line = read_func(fd, line);
	if (!line)
		return (NULL);
	ret = ft_substr(line, 0, ft_strchr(line, '\n'));
	tmp = ft_strdup(line + ft_strchr(line, '\n') + 1);
	free(line);
	line = tmp;
	return (ret);
}

int main()
{
	char *s;
	int fd = open("laboratornaya_krisa.txt", O_RDONLY);
	s = get_next_line(fd);
	printf ("%s\n", s);
	free(s);
	s = get_next_line(fd);
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
	// printf ("%s\n", get_next_line(fd));
	system("leaks a.out");
}