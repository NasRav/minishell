#include "minishell.h"

static int	ft_echo(char **argv)
{
	unsigned int	i;
	int				n;

	i = 1;
	n = 0;
	while (argv[i] && !ft_strcmp(argv[i], "-n"))
		++i;
	if (i > 1)
		n = 1;
	while (argv[i])
	{
		if (*argv[i])
		{
			ft_putstr(argv[i]);
			if (argv[i + 1])
			{
				if ((write(1, " ", 1) == -1))
					return (1);
			}
		}
		++i;
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

static void	ft_pwd(char **envp)
{
	ft_printf("%s\n", ft_getenv("PWD", envp));
}

static int	ft_env(char **argv, char ***envp)
{
	int	i;

	if (argv[1])
	{
		ft_putstr_fd("env: «", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("»: No such file or directory\n", 2);
		return (127);
	}
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strchr((*envp)[i], '='))
			ft_printf("%s\n", (*envp)[i]);
		++i;
	}
	return (0);
}

int	exec_builtin(t_list2 *history, char ***argv, char ***envp)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp("echo", (*argv)[0]))
		exit_status = ft_echo(*argv);
	else if (!ft_strcmp("pwd", (*argv)[0]))
		ft_pwd(*envp);
	else if (!ft_strcmp("exit", (*argv)[0]))
		exit_status = ft_exit(history, *argv);
	else if (!ft_strcmp("cd", (*argv)[0]))
		exit_status = ft_cd(*argv, envp);
	else if (!ft_strcmp("env", (*argv)[0]))
		exit_status = ft_env(*argv, envp);
	else if (!ft_strcmp("export", (*argv)[0]))
		exit_status = ft_export(envp, *argv);
	else if (!ft_strcmp("unset", (*argv)[0]))
		ft_unset(envp, *argv);
	if (exit_status)
		get_errorvar(exit_status, 0);
	return (exit_status);
}
