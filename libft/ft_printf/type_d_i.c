#include "ft_printf.h"

static size_t	output2(size_t bytes, t_flags flag, int f, int ap_i)
{
	if (f == 7)
	{
		if (ap_i < 0)
			bytes = format_putstr("-2147483648", bytes);
		else
			bytes = format_putstr("2147483648", bytes);
	}
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

static void	reflags(t_flags *flag, int f, unsigned int ap_i)
{
	if (flag->left < 0)
		flag->left *= -1;
	if (flag->dot > -1)
		flag->null = ' ';
	if (flag->dot == -1 || flag->dot < (int)ft_len_int(ap_i))
		flag->dot = ft_len_int(ap_i);
	if (flag->right)
	{
		flag->right = flag->right - flag->dot;
		if (!f)
			flag->right++;
	}
	if (flag->left)
	{
		flag->left = flag->left - flag->dot;
		if (!f)
			flag->left++;
	}
	if (flag->dot >= (int)ft_len_int(ap_i))
		flag->dot -= ft_len_int(ap_i);
}

static size_t	output(size_t bytes, t_flags flag, int ap_i, int f)
{
	if (ap_i < 0 && flag.null == '0')
	{
		ap_i *= -1;
		bytes = format_putchar('-', bytes);
	}
	while (flag.right-- > 0)
	{
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
		else
			bytes = format_putchar(' ', bytes);
	}
	if (ap_i < 0 && flag.dot)
	{
		ap_i *= -1;
		bytes = format_putchar('-', bytes);
	}
	while (flag.dot-- > 0)
		bytes = format_putchar('0', bytes);
	if (f == 1 || f == 9)
		bytes = format_putnbr(ap_i, bytes);
	return (output2(bytes, flag, f, ap_i));
}

size_t	type_d_i(va_list ap, size_t bytes, t_flags flag)
{
	int			ap_i;
	int			f;

	ap_i = va_arg(ap, int);
	if (ap_i == -2147483648)
	{
		ap_i++;
		f = 7;
	}
	else if ((int)ft_len_int(ap_i) == flag.dot && ap_i <= -1)
		f = 9;
	else if (!ap_i && !flag.dot)
		f = 0;
	else
		f = 1;
	reflags(&flag, f, ap_i);
	if ((ap_i < 0 && flag.dot) || f == 9)
	{
		flag.dot++;
		if (flag.right)
			flag.right--;
		if (flag.left)
			flag.left--;
	}
	return (output(bytes, flag, ap_i, f));
}
