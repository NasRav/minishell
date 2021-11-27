#include "ft_printf.h"

static size_t	output(size_t bytes, t_flags flag, size_t p_ap, int f)
{
	while (flag.right-- > 0)
	{
		if (flag.null == '0')
			bytes = format_putchar('0', bytes);
		else
			bytes = format_putchar(' ', bytes);
	}
	bytes = format_putstr("0x", bytes);
	while (flag.dot-- > 0)
		bytes = format_putchar('0', bytes);
	if (f)
		bytes = ft_putnbr_p(p_ap, bytes);
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}

static void	is_null(t_flags *flag, long int p_ap)
{
	if (flag->null == '0')
	{
		flag->dot += flag->right;
		flag->right = 0;
	}
	if (flag->null == ' ' && flag->dot && p_ap < 0)
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
	k -= 2;
	return (k);
}

size_t	type_p(va_list ap, size_t bytes, t_flags flag)
{
	size_t	p_ap;
	int		f;

	p_ap = va_arg(ap, size_t);
	if (!p_ap && !flag.dot)
		f = 0;
	else
		f = 1;
	if (flag.dot > -1)
		flag.null = ' ';
	if (flag.dot == -1 || flag.dot < (int)ft_len_p(p_ap))
		flag.dot = ft_len_p(p_ap);
	if (flag.right)
		flag.right = exist(flag.right, flag.dot, f);
	if (flag.left)
		flag.left = exist(flag.left, flag.dot, f);
	if (flag.dot >= (int)ft_len_p(p_ap))
		flag.dot -= ft_len_p(p_ap);
	is_null(&flag, p_ap);
	return (output(bytes, flag, p_ap, f));
}
