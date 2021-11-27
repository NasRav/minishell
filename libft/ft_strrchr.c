#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*str;

	i = 0;
	str = (char *)s;
	while (*str)
	{
		str++;
		i++;
	}
	if (c == 0)
		return ((char *)str);
	while (i > 0)
	{
		str--;
		if (*str == c)
			return (str);
		i--;
	}
	return (0);
}
