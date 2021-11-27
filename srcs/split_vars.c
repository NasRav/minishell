#include "minishell.h"

static void	free_var(char *variable, t_queue **var)
{
	if (!variable)
	{
		free((*var)->line);
		(*var)->line = ft_strdup("\0");
	}
}

void	split_whitespaces(char **result, t_queue **var)
{
	t_queue	*next;
	char	**spaces;
	int		i;

	spaces = ft_split(*result, ' ');
	next = (*var)->next;
	(*var)->next = NULL;
	i = 0;
	while (spaces[i])
	{
		if (i == 0)
		{
			free((*var)->line);
			(*var)->line = ft_strdup(spaces[i]);
		}
		else
		{
			push_queue(0, spaces[i], var);
			(*var) = (*var)->next;
		}
		free(spaces[i++]);
	}
	free_var(spaces[0], var);
	free(spaces);
	(*var)->next = next;
}
