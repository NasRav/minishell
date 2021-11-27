#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!s && !d)
		return ((unsigned char *)d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
