#include "libft.h"

void	*ft_realloc(void *ptr, int size, int newsize)
{
	char	*str;
	char	*new;
	int		i;

	str = (char *)ptr;
	new = (char *)malloc(sizeof(char) * newsize);
	if (!new)
	{
		if (ptr && size != 0)
			free(ptr);
		return (0);
	}
	i = 0;
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	if (ptr && size != 0)
		free(ptr);
	return (new);
}
