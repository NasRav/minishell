#include "minishell.h"

static int	error_valid_number(long long int n)
{
	if (n > 255)
		n %= 256;
	return ((int)n);
}

static int	very_long(char *string, long long int *exit_status)
{
	unsigned long long int	n;
	int						minus;

	minus = 0;
	n = 0;
	if (*string == '-')
	{
		minus = 1;
		++string;
	}
	while (ft_strchr("0123456789", *string) && *string)
	{
		n = n * 10 + ((*string) - '0');
		++string;
		if ((!minus && n > __LONG_MAX__) || (minus && (n - 1) > __LONG_MAX__))
			return (1);
	}
	*exit_status = n;
	if (minus)
		*exit_status *= -1;
	return (0);
}

static int	exit_with_status(char **argv, long long int *error_status)
{
	if (very_long(argv[1], error_status) || (!ft_isnumber(argv[1]) && \
	(!(*argv[1] == '-' && ft_isnumber(argv[1] + 1)))) || \
	(*argv[1] == '-' && !(*(argv[1] + 1))))
	{
		ft_putstr_fd("minish: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*error_status = 255;
	}
	else if (argv[2])
	{
		ft_putstr_fd("minish: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_list2 *history, char **argv)
{
	long long int	error_status;
	int				valid_exit;

	valid_exit = 0;
	term_set(0, 2);
	ft_printf("exit\n");
	if (argv && argv[1])
		valid_exit = exit_with_status(argv, &error_status);
	else
		error_status = (unsigned int)ft_atoi(get_errorvar(0, 1));
	get_errorvar(0, 0);
	if (!valid_exit)
	{
		save_history(&history);
		exit(error_valid_number(error_status));
	}
	else
		return (1);
}
