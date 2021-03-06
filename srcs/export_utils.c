#include "minishell.h"

int	is_valid_val(char *line)
{
	char	*variable;
	char	*value;
	int		ret;

	ret = 0;
	split_env(line, &variable, &value);
	if (ft_strchr("0123456789", *line))
		ret = 1;
	while (*line)
	{
		if (!ft_isalnum(*line) && *line != '_' && \
		(*line != '=' && (*(line + 1))))
			ret = 1;
		++line;
	}
	free(variable);
	if (value)
		free(value);
	return (ret);
}

int	compare_env_var(char *env, char *new_env)
{
	int	ret;

	env = ft_strjoin(env, "=");
	new_env = ft_strjoin(new_env, "=");
	if (!env || !new_env)
		exit(1);
	ret = ft_strncmp(env, new_env, ft_strchr(new_env, '=') - new_env + 1);
	free(env);
	free(new_env);
	return (ret);
}

static void	print_export_string(char **string)
{
	int		i;
	char	*variable;
	char	*value;

	i = 0;
	while (string[i])
	{
		split_env(string[i], &variable, &value);
		ft_printf("declare -x %s", variable);
		if (ft_strchr(variable, '='))
			ft_printf("\"%s\"", value);
		ft_putchar('\n');
		free(variable);
		if (value)
			free(value);
		++i;
	}
}

void	print_export(char **envp)
{
	int		i;
	char	*tmp;
	char	**tmp_env;

	i = 0;
	while (envp[i])
		i++;
	tmp_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp_env)
		exit(1);
	tmp_env = ft_memcpy(tmp_env, envp, sizeof(char *) * (i + 1));
	i = 1;
	while (tmp_env[i])
	{
		if (i > 0 && (ft_strcmp(tmp_env[i], tmp_env[i - 1]) < 0))
		{
			tmp = tmp_env[i - 1];
			tmp_env[i - 1] = tmp_env[i];
			tmp_env[i--] = tmp;
		}
		else
			i++;
	}
	print_export_string(tmp_env);
	free(tmp_env);
}
