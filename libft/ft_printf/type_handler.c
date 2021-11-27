#include "ft_printf.h"

size_t	type_c(va_list ap, size_t bytes, t_flags flag)
{
	if (flag.right)
		flag.right = flag.right - 1;
	if (flag.left)
		flag.left = flag.left - 1;
	while (flag.right-- > 0)
	{
		if (flag.null == ' ')
			bytes = format_putchar(' ', bytes);
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
	}
	bytes = format_putchar(va_arg(ap, int), bytes);
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

size_t	type_s(va_list ap, size_t bytes, t_flags flag)
{
	char	*s_ap;

	s_ap = va_arg(ap, char *);
	if (!s_ap)
		s_ap = "(null)";
	if (flag.left < 0)
		flag.left *= -1;
	if (flag.dot <= -1 || flag.dot > (int)ft_str_len(s_ap))
		flag.dot = ft_str_len(s_ap);
	if (flag.right)
		flag.right = flag.right - flag.dot;
	if (flag.left)
		flag.left = flag.left - flag.dot;
	while (flag.right-- > 0)
	{
		if (flag.null == ' ')
			bytes = format_putchar(' ', bytes);
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
	}
	while (flag.dot-- > 0)
		bytes = format_putchar(*s_ap++, bytes);
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

size_t	type_percent(size_t bytes, t_flags flag)
{
	if (flag.right)
		flag.right = flag.right - 1;
	if (flag.left)
		flag.left = flag.left - 1;
	while (flag.right-- > 0)
	{
		if (flag.null == ' ')
			bytes = format_putchar(' ', bytes);
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
	}
	bytes = format_putchar('%', bytes);
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

size_t	type_asterisk(va_list ap, const char *str, size_t i, int *asterisk)
{
	*asterisk = 0;
	if (str[i] == '*')
	{
		*asterisk = va_arg(ap, int);
		i++;
	}
	if (ft_is_digit(str[i]))
	{
		*asterisk = ft_a_to_i(str + i);
		while (ft_is_digit(str[i]))
			i++;
	}
	return (i);
}
