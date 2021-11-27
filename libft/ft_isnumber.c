#include "libft.h"

int	ft_isnumber(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (0);
		++num;
	}
	return (1);
}
