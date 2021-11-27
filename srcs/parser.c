#include "minishell.h"

void	cmd_init(t_cmd **par)
{
	(*par)->cmd = NULL;
	(*par)->rd = NULL;
	(*par)->next = NULL;
	(*par)->err = 0;
}

static void	check_pipe(t_queue **lex, t_cmd **lnode, t_cmd **par)
{
	if ((*lnode)->cmd == NULL && (*lnode)->rd == NULL)
	{
		(*par)->err = 1;
		ft_putstr_fd("minish: syntax error near unexpected token `|\'\n", 2);
	}
	else if (!(*lex)->next)
	{
		(*par)->err = 1;
		ft_putstr_fd("minish: syntax error near unexpected token `|\'\n", 2);
	}
	else
	{
		(*lnode)->next = (t_cmd *)malloc(sizeof(t_cmd));
		if (!(*lnode)->next)
			exit(1);
		(*lnode) = (*lnode)->next;
		cmd_init(lnode);
	}
}

static int	valid_rd(t_queue **lex)
{
	t_queue	*tmp;

	tmp = (*lex)->next;
	if (!ft_strncmp("<\0", tmp->line, 2))
		return (1);
	if (!ft_strncmp(">\0", tmp->line, 2))
		return (1);
	if (!ft_strncmp("<<\0", tmp->line, 3))
		return (1);
	if (!ft_strncmp(">>\0", tmp->line, 3))
		return (1);
	return (0);
}

static void	check_rd(int mode, t_queue **lex, t_cmd **lnode, t_cmd **par)
{
	if (((*lex)->next && (*lex)->next->option == 0 && valid_rd(lex)) || \
	!(*lex)->next)
	{
		(*par)->err = 1;
		if (mode == 1)
			ft_putstr_fd("minish: syntax error near unexpected token `<\'\n", 2);
		else if (mode == 2)
			ft_putstr_fd("minish: syntax error near unexpected token `>\'\n", 2);
		else if (mode == 3)
			ft_putstr_fd("minish: syntax error near unexpected token `<<\'\n", 2);
		else if (mode == 4)
			ft_putstr_fd("minish: syntax error near unexpected token `>>\'\n", 2);
	}
	else if (!ft_strncmp("|\0", (*lex)->next->line, 2))
	{
		ft_putstr_fd("minish: syntax error near unexpected token `|\'\n", 2);
		(*par)->err = 1;
	}
	else
	{
		free(pop_queue(lex));
		if ((*lex)->option == 2)
			mode *= -1;
		push_queue(mode, (*lex)->line, &(*lnode)->rd);
	}
}

void	parser(t_queue **lex, t_cmd **par)
{
	t_cmd	*lnode;

	lnode = *par;
	while (*lex)
	{
		if ((*lex)->option != 0)
			push_queue((*lex)->option, (*lex)->line, &(lnode->cmd));
		else if ((*par)->err == 0)
		{
			if (!ft_strncmp("|\0", (*lex)->line, 2))
				check_pipe(lex, &lnode, par);
			else if (!ft_strncmp("<\0", (*lex)->line, 2))
				check_rd(1, lex, &lnode, par);
			else if (!ft_strncmp(">\0", (*lex)->line, 2))
				check_rd(2, lex, &lnode, par);
			else if (!ft_strncmp("<<\0", (*lex)->line, 3))
				check_rd(3, lex, &lnode, par);
			else if (!ft_strncmp(">>\0", (*lex)->line, 3))
				check_rd(4, lex, &lnode, par);
			else
				push_queue((*lex)->option, (*lex)->line, &(lnode->cmd));
		}
		free(pop_queue(lex));
	}
}
