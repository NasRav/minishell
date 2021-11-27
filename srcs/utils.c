#include "minishell.h"

int	check_closed(int k, char *str)
{
	char	quote;

	quote = str[k];
	++k;
	while (str[k])
	{
		if (str[k] == quote)
			return (1);
		++k;
	}
	return (0);
}

char	*get_errorvar(int exit_status, int ret)
{
	static char	*error = 0;

	if (ret)
	{
		if (error)
			return (error);
		else
			return ("0");
	}
	if (error)
		free(error);
	if (exit_status)
		error = ft_itoa(exit_status);
	else
		error = 0;
	return (0);
}

char	*ft_getenv(char *key, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp(key, "?"))
			return (get_errorvar(0, 1));
		if (!compare_env_var(envp[i], key))
		{
			if (ft_strchr(envp[i], '='))
				return (ft_strchr(envp[i], '=') + 1);
			else
				return (0);
		}
		++i;
	}
	return (0);
}

char	*ft_getcwd(void)
{
	int		size;
	char	*string;

	size = 10;
	string = (char *)malloc(sizeof(char) * 16);
	if (!string)
		exit(1);
	while (!getcwd(string, size))
	{
		free(string);
		size *= 2;
		string = (char *)malloc(sizeof(char) * size);
		if (!string)
			exit(1);
	}
	return (string);
}
