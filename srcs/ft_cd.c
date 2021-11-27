#include "minishell.h"

static void	change_pwd_value(char ***envp)
{
	char	**argv;
	char	*pwd;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = "export";
	argv[1] = ft_strjoin("OLDPWD=", ft_getenv("PWD", *envp));
	if (!(argv[1]))
		exit(1);
	argv[2] = 0;
	ft_export(envp, argv);
	free(argv[1]);
	pwd = ft_getcwd();
	argv[1] = ft_strjoin("PWD=", pwd);
	if (!(argv[1]))
		exit(1);
	argv[2] = 0;
	ft_export(envp, argv);
	free(argv[1]);
	free(pwd);
	free(argv);
}

static int	change_dir(char *new_dir, char ***envp)
{
	if (chdir(new_dir))
	{
		ft_putstr_fd("minish: cd: ", 2);
		ft_putstr_fd(new_dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
	}
	else
		change_pwd_value(envp);
	return (errno);
}

int	ft_cd(char **argv, char ***envp)
{
	char	*next_dir;

	if (!argv[1])
		next_dir = ft_getenv("HOME", *envp);
	else
		next_dir = argv[1];
	if (change_dir(next_dir, envp))
		return (1);
	return (0);
}
