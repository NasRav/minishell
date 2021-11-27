#include "minishell.h"

char	*char_to_str(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static int	delimiter(int i, char *line, char **tok, t_queue **lex)
{
	if ((line[i] == '\'' || line[i] == '\"') && check_closed(i, line))
		i += parse_quot(line[i], line + i, tok, lex);
	else if (line[i] == '|')
		i += parse_pipe(tok, lex);
	else if (line[i] == '<' || line[i] == '>')
		i += parse_rd(line + i, tok, lex);
	else if (line[i] == ' ')
	{
		if (*tok)
		{
			if (**tok != '\0')
				push_queue(0, *tok, lex);
			free(*tok);
			(*tok) = NULL;
		}
		(*tok) = ft_strdup("\0");
	}
	else if (line[i] != ' ')
		join_free(1, tok, char_to_str(line[i]));
	return (i);
}

void	lexer(char *line, t_queue **lex)
{
	char	*token;
	int		i;

	token = ft_strdup("\0");
	if (!token)
		exit(1);
	i = 0;
	while (line[i])
	{
		i = delimiter(i, line, &token, lex);
		++i;
	}
	if (token)
	{
		if (*token != '\0')
			push_queue(0, token, lex);
		free(token);
		token = NULL;
	}
}
