#include "ft_printf.h"

size_t	ft_putnbr_p(size_t nbr, size_t bytes)
{
	if (nbr >= 16)
	{
		bytes = ft_putnbr_p(nbr / 16, bytes);
		if (nbr % 16 < 10)
			bytes = format_putchar(nbr % 16 + '0', bytes);
		else
			bytes = format_putchar(nbr % 16 - 10 + 'a', bytes);
	}
	else
	{
		if (nbr < 10)
			bytes = format_putchar(nbr + '0', bytes);
		else
			bytes = format_putchar(nbr - 10 + 'a', bytes);
	}
	return (bytes);
}

size_t	ft_putnbr_u(unsigned int nbr, size_t bytes)
{
	if (nbr == 2147483648)
		bytes = format_putstr("2147483648", bytes);
	else if (nbr >= 10)
	{
		bytes = ft_putnbr_u(nbr / 10, bytes);
		bytes = format_putchar(nbr % 10 + '0', bytes);
	}
	else
		bytes = format_putchar(nbr + '0', bytes);
	return (bytes);
}

size_t	ft_putnbr_x(unsigned int nbr, size_t bytes)
{
	if (nbr >= 16)
	{
		bytes = ft_putnbr_x(nbr / 16, bytes);
		if (nbr % 16 < 10)
			bytes = format_putchar(nbr % 16 + '0', bytes);
		else
			bytes = format_putchar(nbr % 16 - 10 + 'a', bytes);
	}
	else
	{
		if (nbr < 10)
			bytes = format_putchar(nbr + '0', bytes);
		else
			bytes = format_putchar(nbr - 10 + 'a', bytes);
	}
	return (bytes);
}

size_t	ft_putnbr_xx(unsigned int nbr, size_t bytes)
{
	if (nbr >= 16)
	{
		bytes = ft_putnbr_xx(nbr / 16, bytes);
		if (nbr % 16 < 10)
			bytes = format_putchar(nbr % 16 + '0', bytes);
		else
			bytes = format_putchar(nbr % 16 - 10 + 'A', bytes);
	}
	else
	{
		if (nbr < 10)
			bytes = format_putchar(nbr + '0', bytes);
		else
			bytes = format_putchar(nbr - 10 + 'A', bytes);
	}
	return (bytes);
}
