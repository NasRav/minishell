#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	while (dst[i] && i < size)
		i++;
	if (size != 0)
	{
		while (src[j] && i + j < size - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
	}
	if (i + j < size)
		dst[i + j] = '\0';
	return (i + src_len);
}
