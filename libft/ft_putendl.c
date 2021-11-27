#include "libft.h"

void	ft_putendl(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
	ft_putchar('\n');
}
