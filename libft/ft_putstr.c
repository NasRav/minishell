#include "libft.h"

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		ft_putchar(*s++);
}
