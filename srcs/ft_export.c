#include "minishell.h"

static int	set_env(char ***envp, char *variable, char *value)
{
	int		j;
	int		ret;

	j = -1;
	ret = 0;
	while ((*envp)[++j] && !ret)
	{
		if (!compare_env_var((*envp)[j], variable))
		{
			ret = 1;
			if (value && compare_env_var("_=", variable))
			{
				free((*envp)[j]);
				join_free(1, &variable, value);
				(*envp)[j] = variable;
				variable = 0;
				value = 0;
			}
		}
	}
	if (variable)
		free(variable);
	if (value)
		free(value);
	return (ret);
}

int	add_to_env(char ***envp, char *argv)
{
	int		k;
	char	**new_envp;

	if (is_valid_val(argv))
	{
		free(argv);
		return (1);
	}
	k = 0;
	while ((*envp)[k])
		++k;
	new_envp = (char **)malloc(sizeof(char *) * (k + 2));
	if (!new_envp)
		exit(1);
	new_envp = ft_memcpy(new_envp, *envp, sizeof(char *) * (k + 2));
	free(*envp);
	*envp = new_envp;
	new_envp[k] = argv;
	new_envp[k + 1] = 0;
	return (0);
}

void	split_env(char *string, char **variable, char **value)
{
	char	*equal;

	equal = ft_strchr(string, '=');
	if (equal)
	{
		*variable = ft_substr(string, 0, equal + 1 - string);
		*value = ft_strdup(equal + 1);
		if (!(*variable) || !(*value))
			exit(1);
	}
	else
	{
		*variable = ft_strdup(string);
		if (!(*variable))
			exit(1);
		*value = 0;
	}
}

static int	error_export(char *line)
{
	char	*variable;
	char	*value;
	char	*tmp;

	split_env(line, &variable, &value);
	if (ft_strchr(variable, '='))
	{
		tmp = variable;
		variable = ft_substr(variable, 0, ft_strchr(variable, '=') - variable);
		free(tmp);
	}
	ft_putstr_fd("minish: export: `", 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(variable);
	if (value)
		free(value);
	return (1);
}

int	ft_export(char ***envp, char **argv)
{
	int		i;
	char	*variable;
	char	*value;
	int		ret;

	ret = 0;
	if (!argv[1])
		print_export(*envp);
	else
	{
		i = 1;
		while (argv[i])
		{
			split_env(argv[i], &variable, &value);
			if (!set_env(envp, variable, value))
			{
				if (add_to_env(envp, ft_strdup(argv[i])))
					ret = error_export(argv[i]);
			}
			i++;
		}
	}
	return (ret);
}
