#include "libft.h"

static char	*ret_nul(void)
{
	char		*dest;

	dest = malloc(sizeof(char));
	if (!dest)
		return (0);
	*dest = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dest;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		dest = ret_nul();
		return (dest);
	}
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
