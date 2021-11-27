#include "minishell.h"

static void	key_value(int i, char *copy, char **result, char **envp)
{
	char	*env;

	env = ft_strdup("");
	if (!env)
		exit(1);
	while (copy[i])
	{
		if (copy[i] == '$')
		{
			if (env[0] == '\0')
				join_free(1, result, char_to_str('$'));
			else if (ft_getenv(env, envp))
				join_free(0, result, ft_getenv(env, envp));
			free(env);
			env = ft_strdup("");
		}
		else
			join_free(1, &env, char_to_str(copy[i]));
		++i;
	}
	if (env[0] == '\0')
		join_free(1, result, char_to_str('$'));
	else if (ft_getenv(env, envp))
		join_free(0, result, ft_getenv(env, envp));
	free(env);
}

static void	get_value(t_queue **var, char **envp)
{
	char	*copy;
	char	*result;
	int		i;

	copy = ft_strdup((*var)->line);
	if (!copy)
		exit(1);
	i = 0;
	while (copy[i] != '$')
		++i;
	copy[i++] = '\0';
	result = ft_strdup(copy);
	if (!result)
		exit(1);
	key_value(i, copy, &result, envp);
	split_whitespaces(&result, var);
	free(result);
	free(copy);
}

static void	set_cmd(t_cmd **tpar, char **envp)
{
	t_queue	*tqueue;

	if ((*tpar)->cmd)
	{
		tqueue = (*tpar)->cmd;
		while (tqueue)
		{
			if (tqueue->option != 2 && ft_strchr(tqueue->line, '$'))
				get_value(&tqueue, envp);
			tqueue = tqueue->next;
		}
	}
}

static void	set_rd(t_cmd **tpar, char **envp)
{
	t_queue	*tqueue;

	if ((*tpar)->rd)
	{
		tqueue = (*tpar)->rd;
		while (tqueue)
		{
			if (tqueue->option > 0 && ft_strchr(tqueue->line, '$'))
				get_value(&tqueue, envp);
			tqueue = tqueue->next;
		}
	}
}

void	get_from_env(t_cmd **par, char **envp)
{
	t_cmd	*tpar;

	if (*par)
	{
		tpar = *par;
		while (tpar)
		{
			set_cmd(&tpar, envp);
			set_rd(&tpar, envp);
			tpar = tpar->next;
		}
	}
}
