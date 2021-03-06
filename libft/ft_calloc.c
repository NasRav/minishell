#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c;

	c = (char *)malloc(nmemb * size);
	if (!c)
		return (0);
	ft_bzero(c, nmemb * size);
	return (c);
}
