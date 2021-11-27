#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	index;
	size_t	rtrn;
	va_list	ap;

	index = 0;
	rtrn = 0;
	va_start(ap, format);
	while (format[index])
	{
		if (format[index] == '%')
		{
			index++;
			index = check_flags(format, ap, index, &rtrn);
		}
		else
			rtrn = format_putchar(format[index], rtrn);
		if (!format[index])
			break ;
		index++;
	}
	va_end(ap);
	return (rtrn);
}
