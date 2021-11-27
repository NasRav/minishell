#include "minishell.h"

void	push_queue(int opt, char *line, t_queue **queue)
{
	t_queue	*tmp;

	if (*queue)
	{
		tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_queue *)malloc(sizeof(t_queue));
		if (line)
			tmp->next->line = ft_strdup(line);
		tmp->next->option = opt;
		tmp->next->next = NULL;
	}
	else
	{
		(*queue) = (t_queue *)malloc(sizeof(t_queue));
		if (line)
			(*queue)->line = ft_strdup(line);
		(*queue)->option = opt;
		(*queue)->next = NULL;
	}
}

char	*pop_queue(t_queue **queue)
{
	t_queue	*tmp;
	char	*out;

	out = NULL;
	if (*queue)
	{
		tmp = *queue;
		(*queue) = (*queue)->next;
		if (tmp->line)
		{
			out = ft_strdup(tmp->line);
			free(tmp->line);
		}
		free(tmp);
		tmp = NULL;
	}
	return (out);
}
