#include "minishell.h"

static void	free_cmd(t_cmd **par)
{
	while ((*par)->cmd != NULL)
		free(pop_queue(&((*par)->cmd)));
	while ((*par)->rd != NULL)
		free(pop_queue(&((*par)->rd)));
}

static void	free_parser(t_cmd **par)
{
	t_cmd	*tmp;

	while (*par != NULL)
	{
		free_cmd(par);
		tmp = *par;
		(*par) = (*par)->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	clean_par(t_cmd **par)
{
	t_queue	*tmp;
	t_queue	*prev;
	t_queue	*empty;

	if ((*par) && (*par)->cmd)
	{
		tmp = (*par)->cmd;
		while (tmp)
		{
			if (tmp->option == 0 && *(tmp->line) == '\0')
			{
				empty = tmp->next;
				prev->next = empty;
				free(tmp->line);
				free(tmp);
				tmp = NULL;
				tmp = prev;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	handle_cmdline(t_list2 *history, char ***envp)
{
	t_queue	*lex;
	t_cmd	*parse;

	if (history->content)
	{
		lex = NULL;
		parse = (t_cmd *)malloc(sizeof(t_cmd));
		if (!parse)
			exit(1);
		cmd_init(&parse);
		lexer(history->content, &lex);
		parser(&lex, &parse);
		get_from_env(&parse, *envp);
		clean_par(&parse);
		if (parse)
			executor(history, envp, &parse);
		free_parser(&parse);
	}
}
