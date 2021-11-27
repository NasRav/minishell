#include "minishell.h"

void	reset_fds(int mode)
{
	static int	input;
	static int	output;

	if (mode)
	{
		input = dup(0);
		output = dup(1);
	}
	else
	{
		dup2(input, 0);
		dup2(output, 1);
		close(input);
		close(output);
	}
}

void	ft_pipe(t_cmd *tmp, int fd[2], pid_t pid)
{
	static int	i = 0;
	static int	next_input = 0;
	static int	fd_out = 0;

	if (!i)
		reset_fds(1);
	if (i)
	{
		dup2(next_input, 0);
		dup2(fd_out, 1);
		close(next_input);
	}
	if (tmp->next)
	{
		if (!pid)
			close(fd[0]);
		fd_out = dup(1);
		dup2(fd[1], 1);
		close(fd[1]);
		next_input = fd[0];
		i = 1;
	}
	else
		i = 0;
}

pid_t	fork_pids(pid_t **pids)
{
	pid_t	*tmp;
	int		size;
	int		j;

	size = 0;
	if (*pids)
		while ((*pids)[size])
			++size;
	tmp = *pids;
	*pids = (pid_t *)malloc(sizeof(pid_t) * (++size + 1));
	if (!(*pids))
		exit(1);
	j = 0;
	while (j < (size - 1))
	{
		(*pids)[j] = tmp[j];
		++j;
	}
	(*pids)[size - 1] = fork();
	(*pids)[size] = 0;
	if (tmp)
		free(tmp);
	return ((*pids)[size - 1]);
}

void	wait_pids(pid_t *pids)
{
	int	pid_count;
	int	i;
	int	wstatus;

	if (pids)
	{
		pid_count = 0;
		while (pids[pid_count])
			++pid_count;
		i = 0;
		while (i < pid_count)
		{
			waitpid(pids[i], &wstatus, 0);
			++i;
		}
		free(pids);
		if (WIFEXITED(wstatus))
			get_errorvar(WEXITSTATUS(wstatus), 0);
	}
}
