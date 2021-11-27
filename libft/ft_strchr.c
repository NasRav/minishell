#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == c && c != 0)
			return (str);
		str++;
	}
	if (!*str && !c)
		return ((char *)str);
	return (0);
}
