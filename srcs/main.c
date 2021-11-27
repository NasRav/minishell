#include "minishell.h"

t_term	*term_set(t_term *term, int term_n)
{
	static struct termios	initial_term;

	if (term_n == 1)
		tcsetattr(0, TCSANOW, &term->icanon_term);
	else if (term_n == 2)
		tcsetattr(0, TCSANOW, &initial_term);
	else
	{
		term = ft_calloc(1, sizeof(t_term));
		tcgetattr(0, &initial_term);
		tgetent(0, getenv("TERM"));
		ft_memcpy(&term->icanon_term, &initial_term, sizeof(struct termios));
		term->icanon_term.c_lflag &= ~(ECHO);
		term->icanon_term.c_lflag &= ~(ICANON);
		term->icanon_term.c_lflag &= ~(ISIG);
		term->history = get_history();
	}
	return (term);
}

static char	**get_env(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		++i;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		exit(1);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			exit(1);
		++i;
	}
	new_envp[i] = 0;
	return (new_envp);
}

void	sig_handler(int sig_num)
{
	int	sig;

	wait(&sig);
	if (sig == sig_num)
	{
		if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
		else if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_term		*term;

	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	term = 0;
	term = term_set(term, 0);
	envp = get_env(envp);
	while (1)
	{
		ft_putstr("minish$ ");
		if (get_cmd(term))
			handle_cmdline(term->history, &envp);
	}
	return (0);
}
