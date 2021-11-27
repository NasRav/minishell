#include "ft_printf.h"

static size_t	output(size_t bytes, t_flags flag, size_t x_ap, int f)
{
	while (flag.right-- > 0)
	{
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
		else
			bytes = format_putchar(' ', bytes);
	}
	while (flag.dot-- > 0)
		bytes = format_putchar('0', bytes);
	if (f)
	{
		if (flag.x == 'x')
			bytes = ft_putnbr_x(x_ap, bytes);
		if (flag.x == 'X')
			bytes = ft_putnbr_xx(x_ap, bytes);
	}
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

static void	is_null(t_flags *flag, long int x_ap)
{
	if (flag->null == '0')
	{
		flag->dot += flag->right;
		flag->right = 0;
	}
	if (flag->null == ' ' && flag->dot && x_ap < 0)
	{
		flag->dot++;
		if (flag->right)
			flag->right--;
	}
}

static int	exist(int k, int dot, int f)
{
	k = k - dot;
	if (!f)
		k++;
	return (k);
}

size_t	type_x(va_list ap, size_t bytes, t_flags flag)
{
	unsigned int	x_ap;
	int				f;

	x_ap = va_arg(ap, size_t);
	if (!x_ap && !flag.dot)
		f = 0;
	else
		f = 1;
	if (flag.dot > -1)
		flag.null = ' ';
	if (flag.dot == -1 || flag.dot < (int)ft_len_x(x_ap))
		flag.dot = ft_len_x(x_ap);
	if (flag.right)
		flag.right = exist(flag.right, flag.dot, f);
	if (flag.left)
		flag.left = exist(flag.left, flag.dot, f);
	if (flag.dot >= (int)ft_len_x(x_ap))
		flag.dot -= ft_len_x(x_ap);
	is_null(&flag, x_ap);
	return (output(bytes, flag, x_ap, f));
}
