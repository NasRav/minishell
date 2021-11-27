#include "ft_printf.h"

size_t	ft_str_len(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isflag(int c)
{
	if (c == '-' || c == '*' || c == '.' || ft_is_digit(c))
		return (1);
	else
		return (0);
}

int	ft_a_to_i(const char *nptr)
{
	int			sign;
	long int	num;

	num = 0;
	sign = 1;
	while (*nptr && (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' || \
			*nptr == '\f' || *nptr == '\r' || *nptr == ' '))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (num > num * 10 + (*nptr - '0') && sign == 1)
			return (-1);
		else if (num > num * 10 + (*nptr - '0') && sign == -1)
			return (0);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * num);
}
