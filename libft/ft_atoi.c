#include "libft.h"

int	ft_atoi(const char *nptr)
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
