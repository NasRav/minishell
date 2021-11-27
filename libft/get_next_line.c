#include "libft.h"

static char	*ft_strcat_alloc(char const *s1, char const *s2)
{
	char	*concat;
	size_t	size;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	size = len1 + len2 + 1;
	concat = (char *)malloc(sizeof(char) * (size));
	if (!concat)
		return (0);
	ft_strlcpy(concat, s1, len1 + 1);
	if (ft_strlcat(concat, s2, size) != len1 + len2)
		return (0);
	return (concat);
}

static int	read_line(int fd, char **buf)
{
	char	tmp[BUFFER_SIZE + 1];
	char	*free_ptr;
	int		rtrn;

	rtrn = read(fd, tmp, BUFFER_SIZE);
	while (rtrn > 0)
	{
		tmp[rtrn] = 0;
		free_ptr = *buf;
		*buf = ft_strcat_alloc(*buf, tmp);
		if (!*buf)
			return (-1);
		free(free_ptr);
		free_ptr = NULL;
		if (ft_strchr(*buf, '\n'))
			return (1);
		rtrn = read(fd, tmp, BUFFER_SIZE);
	}
	return (rtrn);
}

static char	*trim_line(char **buf)
{
	char	*tmp;
	char	*line;
	char	*end_line;
	size_t	len;

	tmp = *buf;
	end_line = ft_strchr(*buf, '\n');
	if (end_line)
		len = end_line - *buf;
	else
		len = ft_strlen(*buf);
	line = ft_substr(*buf, 0, len);
	if (!line)
		return (NULL);
	len++;
	*buf = ft_substr(*buf, len, ft_strlen(*buf) - len);
	if (!buf)
	{
		free(line);
		line = NULL;
	}
	free(tmp);
	tmp = NULL;
	return (line);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf[FOPEN_MAX];
	int			rtrn;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!buf[fd])
		buf[fd] = ft_strdup("");
	if (!buf[fd])
		return (-1);
	rtrn = read_line(fd, &buf[fd]);
	if (rtrn < 0)
		return (-1);
	if (ft_strchr(buf[fd], '\n'))
		rtrn = 1;
	*line = trim_line(&buf[fd]);
	if (!line || !rtrn)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		if (!line)
			return (-1);
	}
	return (rtrn);
}
