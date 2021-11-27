#include "ft_printf.h"

static void	reflags2(t_flags *flag, long int u_ap)
{
	if (flag->dot >= (int)ft_len_u(u_ap))
		flag->dot -= ft_len_u(u_ap);
	if (flag->null == '0')
	{
		flag->dot += flag->right;
		flag->right = 0;
	}
	if (flag->null == ' ' && u_ap < 0 && flag->dot)
	{
		flag->dot++;
		if (flag->right)
			flag->right--;
	}
}

static void	reflags(t_flags *flag, int f, unsigned int u_ap)
{
	if (flag->dot > -1)
		flag->null = ' ';
	if (flag->dot == -1 || flag->dot < (int)ft_len_u(u_ap))
		flag->dot = ft_len_u(u_ap);
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
	reflags2(&*flag, u_ap);
}

size_t	type_u(va_list ap, size_t bytes, t_flags flag)
{
	unsigned int	u_ap;
	int				f;

	u_ap = va_arg(ap, unsigned int);
	if (!u_ap && !flag.dot)
		f = 0;
	else
		f = 1;
	reflags(&flag, f, u_ap);
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
		bytes = ft_putnbr_u(u_ap, bytes);
	while (flag.left-- > 0)
		bytes = format_putchar(' ', bytes);
	return (bytes);
}
