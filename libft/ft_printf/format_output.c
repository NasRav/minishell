#include "ft_printf.h"

size_t	format_putchar(char c, size_t bytes)
{
	write(1, &c, 1);
	bytes++;
	return (bytes);
}

size_t	format_putstr(char *s, size_t bytes)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		bytes = format_putchar(s[i], bytes);
		i++;
	}
	return (bytes);
}

size_t	format_putnbr(int nbr, size_t bytes)
{
	if (nbr == -2147483648)
		bytes = format_putstr("-2147483648", bytes);
	else if (nbr < 0)
	{
		bytes = format_putchar('-', bytes);
		bytes = format_putnbr(-nbr, bytes);
	}
	else if (nbr >= 10)
	{
		bytes = format_putnbr(nbr / 10, bytes);
		bytes = format_putchar(nbr % 10 + '0', bytes);
	}
	else
		bytes = format_putchar(nbr + '0', bytes);
	return (bytes);
}
