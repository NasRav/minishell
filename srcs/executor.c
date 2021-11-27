#include "minishell.h"

static int	is_builtin(char *cmd)
{
	int		i;
	char	**cmd_arr;

	cmd_arr = ft_split("echo cd pwd export unset env exit", ' ');
	i = 0;
	while (cmd_arr[i])
	{
		if (!ft_strcmp(cmd_arr[i], cmd))
		{
			free_array(cmd_arr);
			return (0);
		}
		++i;
	}
	free_array(cmd_arr);
	return (1);
}

static int	check_redirect(int std_in, t_queue *rd)
{
	t_queue	*tmp;
	int		out;

	tmp = rd;
	out = 0;
	while (tmp && out >= 0)
	{
		if (tmp->option == 1)
			out = rd_left(tmp);
		else if (tmp->option == 2)
			out = rd_right(tmp);
		else if (tmp->option == 3)
			out = rd_heredoc(std_in, tmp);
		else if (tmp->option == 4)
			out = rd_append(tmp);
		tmp = tmp->next;
	}
	return (out);
}

static int	look_for_cmd(t_list2 *history, char ***envp, t_queue *cmd)
{
	char	**argv;
	char	**path_arr;
	int		exit_status;

	if (!cmd || !cmd->line)
		return (0);
	exit_status = 0;
	if (!is_builtin(cmd->line))
	{
		set_cmd_queue(&argv, cmd);
		exit_status = exec_builtin(history, &argv, envp);
		free_array(argv);
		return (exit_status);
	}
	path_arr = ft_split(ft_getenv("PATH", *envp), ':');
	execute(path_arr, envp, cmd);
	free_array(path_arr);
	return (exit_status);
}

static void	set_rd_fd(t_list2 *history, char ***envp, t_cmd *tmp, t_cmd *par)
{
	int		save_in;
	int		save_out;
	int		err;
	int		builtin_exit;

	builtin_exit = 0;
	save_in = dup(0);
	save_out = dup(1);
	err = 0;
	if (tmp->rd)
		err = check_redirect(save_out, tmp->rd);
	if (err != -1)
		builtin_exit = look_for_cmd(history, envp, tmp->cmd);
	if ((dup2(save_in, 0)) == -1 || (dup2(save_out, 1)) == -1)
		exit(errno);
	close(save_in);
	close(save_out);
	if (par->next)
		exit (builtin_exit);
}

void	executor(t_list2 *history, char ***envp, t_cmd **par)
{
	t_cmd	*tmp;
	pid_t	pid;
	pid_t	*pids;
	int		fd_p[2];

	pids = 0;
	tmp = *par;
	while (tmp && tmp->err != 1)
	{
		pid = 0;
		if ((tmp->cmd && is_builtin(tmp->cmd->line)) || (*par)->next)
		{
			if (tmp->next)
				pipe(fd_p);
			pid = fork_pids(&pids);
			if ((*par)->next)
				ft_pipe(tmp, fd_p, pid);
		}
		if (!pid)
			set_rd_fd(history, envp, tmp, *par);
		tmp = tmp->next;
	}
	if ((*par)->next)
		reset_fds(0);
	wait_pids(pids);
}
