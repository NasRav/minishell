#include "minishell.h"

int	rd_left(t_queue *rd)
{
	int	file;

	file = open(rd->line, O_RDONLY, 0777);
	if (file < 0)
	{
		ft_putstr_fd("minish: no such file or directory: ", 2);
		ft_putstr_fd(rd->line, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if ((dup2(file, 0)) == -1)
		exit(4);
	close(file);
	return (0);
}

int	rd_right(t_queue *rd)
{
	int	file;

	file = open(rd->line, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (file < 0)
	{
		ft_putstr_fd("minish: can't operate with ", 2);
		ft_putstr_fd(rd->line, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if ((dup2(file, 1)) == -1)
		exit(4);
	close(file);
	return (0);
}

int	rd_append(t_queue *rd)
{
	int	file;

	file = open(rd->line, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (file < 0)
	{
		ft_putstr_fd("minish: can't operate with ", 2);
		ft_putstr_fd(rd->line, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if ((dup2(file, 1)) == -1)
		exit(4);
	close(file);
	return (0);
}

static void	heredoc(int std_in, int file, t_queue *rd)
{
	char	*line;

	while (1)
	{
		write(std_in, "> ", 2);
		get_next_line(std_in, &line);
		if (!ft_strcmp(line, rd->line))
		{
			free(line);
			break ;
		}
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
}

int	rd_heredoc(int std_in, t_queue *rd)
{
	int		file;

	file = open(".minish_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	heredoc(std_in, file, rd);
	close(file);
	file = open(".minish_heredoc", O_RDONLY, 0777);
	if (file < 0)
	{
		ft_putstr_fd("minish: no such file or directory: ", 2);
		ft_putstr_fd(rd->line, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if ((dup2(file, 0)) == -1)
		exit (4);
	close(file);
	return (0);
}
