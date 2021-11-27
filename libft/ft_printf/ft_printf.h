#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_flags
{
	char	null;
	int		right;
	int		left;
	int		dot;
	char	x;
}			t_flags;

int		ft_printf(const char *format, ...);

size_t	format_putchar(char c, size_t bytes);
size_t	format_putstr(char *s, size_t bytes);
size_t	format_putnbr(int nbr, size_t bytes);

size_t	ft_putnbr_p(size_t nbr, size_t bytes);
size_t	ft_putnbr_u(unsigned int nbr, size_t bytes);
size_t	ft_putnbr_x(unsigned int nbr, size_t bytes);
size_t	ft_putnbr_xx(unsigned int nbr, size_t bytes);

size_t	type_asterisk(va_list ap, const char *format, size_t i, \
		int *star);
size_t	check_flags(const char *format, va_list ap, size_t i, \
		size_t *bytes);
int		ft_a_to_i(const char *str);
int		ft_is_digit(int c);
int		ft_isflag(int c);

size_t	ft_str_len(const char *str);
size_t	ft_len_int(int nbr);
size_t	ft_len_p(size_t nbr);
size_t	ft_len_u(unsigned int nbr);
size_t	ft_len_o(unsigned int nbr);
size_t	ft_len_x(unsigned int nbr);

size_t	type_c(va_list ap, size_t bytes, t_flags flag);
size_t	type_d_i(va_list ap, size_t bytes, t_flags flag);
size_t	type_p(va_list ap, size_t bytes, t_flags flag);
size_t	type_percent(size_t bytes, t_flags flag);
size_t	type_s(va_list ap, size_t bytes, t_flags flag);
size_t	type_u(va_list ap, size_t bytes, t_flags flag);
size_t	type_x(va_list ap, size_t bytes, t_flags flag);

#endif
