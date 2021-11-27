#include "minishell.h"

int	parse_pipe(char **tok, t_queue **lex)
{
	if (*tok)
	{
		if (**tok != '\0')
			push_queue(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("|");
	if (!(*tok))
		exit(1);
	if (*tok)
	{
		push_queue(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	if (!(*tok))
		exit(1);
	return (0);
}

static void	check_quot(char quot, char *line, char **tok, t_queue **lex)
{
	if (*tok)
	{
		if (quot == '\'' && (**tok) != '\0')
		{
			if (!(*(line + 1)) || *(line + 1) == ' ')
				push_queue(2, *tok, lex);
		}
		else if (!(*(line + 1)) || *(line + 1) == ' ')
			push_queue(1, *tok, lex);
		if (!(*(line + 1)) || *(line + 1) == ' ')
		{
			free(*tok);
			(*tok) = NULL;
		}
	}
	if (!(*(line + 1)) || *(line + 1) == ' ')
		(*tok) = ft_strdup("\0");
	if (!(*tok))
		exit(1);
}

int	parse_quot(char quot, char *line, char **tok, t_queue **lex)
{
	int	count;

	count = 1;
	while (line[count] != quot)
	{
		join_free(1, tok, char_to_str(line[count]));
		count++;
	}
	if (line[count] == '\'' || line[count] == '\"')
		check_quot(quot, line + count, tok, lex);
	return (count);
}

static int	push_rd(char **tok, t_queue **lex)
{
	int	out;

	out = 0;
	if (*tok)
	{
		out = ft_strlen(*tok);
		push_queue(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	(*tok) = ft_strdup("\0");
	if (!(*tok))
		exit(1);
	return (out - 1);
}

int	parse_rd(char *line, char **tok, t_queue **lex)
{
	if (*tok)
	{
		if (**tok != '\0')
			push_queue(0, *tok, lex);
		free(*tok);
		(*tok) = NULL;
	}
	if (line[0] == '<' && line[1] == '<')
		(*tok) = ft_strdup("<<");
	else if (line[0] == '>' && line[1] == '>')
		(*tok) = ft_strdup(">>");
	else if (line[0] == '<')
		(*tok) = ft_strdup("<");
	else if (line[0] == '>')
		(*tok) = ft_strdup(">");
	return (push_rd(tok, lex));
}
