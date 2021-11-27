#include "minishell.h"

static void	ft_error(char *err_arg)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(err_arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	set_cmd_queue(char ***argv, t_queue *cmd)
{
	t_queue	*tmp;
	int		j;

	j = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		++j;
	}
	(*argv) = (char **)malloc(sizeof(char *) * (j + 1));
	if (!(*argv))
		exit(1);
	j = 0;
	tmp = cmd;
	while (tmp)
	{
		(*argv)[j] = ft_strdup(tmp->line);
		if (!((*argv)[j++]))
			exit(1);
		tmp = tmp->next;
	}
	(*argv)[j] = NULL;
}

void	execute(char **path_arr, char ***envp, t_queue *cmd)
{
	char	**argv;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	set_cmd_queue(&argv, cmd);
	execve(cmd->line, argv, (*envp));
	if (path_arr && *(cmd->line) != '.')
	{
		while (path_arr[i])
		{
			path = ft_strjoin(path_arr[i], "/");
			tmp = path;
			path = ft_strjoin(path, cmd->line);
			execve(path, argv, (*envp));
			free(tmp);
			free(path);
			++i;
		}
	}
	free_array(argv);
	ft_error(cmd->line);
	exit(127);
}
