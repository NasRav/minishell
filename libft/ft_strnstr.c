#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t l)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*lil;

	b = (char *)big;
	lil = (char *)little;
	i = 0;
	if (*lil == '\0')
		return (b);
	while (i < l && b[i])
	{
		j = 0;
		while (b[i + j] == lil[j] && i + j <= l)
		{
			if (lil[j + 1] == '\0')
				return (&b[i]);
			j++;
		}
		i++;
	}
	return (0);
}
