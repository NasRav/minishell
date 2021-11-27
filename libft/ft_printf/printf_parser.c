#include "ft_printf.h"

static size_t	flag_type(va_list ap, char c, t_flags flag, size_t bytes)
{
	if (c == '%')
		bytes = type_percent(bytes, flag);
	if (c == 'c')
		bytes = type_c(ap, bytes, flag);
	if (c == 's')
		bytes = type_s(ap, bytes, flag);
	if (c == 'd' || c == 'i')
		bytes = type_d_i(ap, bytes, flag);
	if (c == 'u')
		bytes = type_u(ap, bytes, flag);
	if (c == 'p')
		bytes = type_p(ap, bytes, flag);
	if (c == 'x' || c == 'X')
	{
		flag.x = c;
		bytes = type_x(ap, bytes, flag);
	}
	return (bytes);
}

static void	reset_flags(t_flags *flag)
{
	if (flag->left < 0)
		flag->left *= -1;
	if (flag->right < 0)
	{
		flag->left = flag->right;
		flag->left *= -1;
		flag->right = 0;
	}
}

size_t	check_flags(const char *format, va_list ap, size_t i, size_t *bytes)
{
	t_flags		flag;

	flag.null = ' ';
	flag.right = 0;
	flag.left = 0;
	flag.dot = -1;
	while (ft_isflag(format[i]))
	{
		if (format[i] == '-' && format[i++])
			i = type_asterisk(ap, format, i, &flag.left);
		if (format[i] == '0' && format[i++])
			flag.null = '0';
		if (format[i] == '.' && format[i++])
			i = type_asterisk(ap, format, i, &flag.dot);
		if (ft_is_digit(format[i]) || format[i] == '*')
			i = type_asterisk(ap, format, i, &flag.right);
	}
	reset_flags(&flag);
	*bytes = flag_type(ap, format[i], flag, *bytes);
	return (i);
}
