#include "minishell.h"

int	arrow_key_press(t_term *term, char n)
{
	if (n == 'C' && term->curs != ft_strlen(term->cmd_line->content))
	{
		tputs(cursor_right, 1, my_putchar);
		++term->curs;
		return (1);
	}
	else if (n == 'D' && term->curs != 0)
	{
		tputs(cursor_left, 1, my_putchar);
		--term->curs;
		return (1);
	}
	else if (n == 'A' || n == 'B')
		put_history(term, n);
	return (0);
}

char	ctrl_c(t_term *term)
{
	if (term->cmd_line->content)
	{
		free(term->cmd_line->content);
		term->cmd_line->content = ft_strdup("");
		if (!term->cmd_line->content)
			exit(1);
	}
	return ('\n');
}

static char	*delete_ch(char *str, int d)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (i != d)
		{
			new_str[j] = str[i];
			++j;
		}
		++i;
	}
	new_str[j] = 0;
	return (new_str);
}

char	backspace(t_term *term)
{
	char	*tmp;

	if (arrow_key_press(term, 'D'))
	{
		tmp = term->cmd_line->content;
		term->cmd_line->content = delete_ch(tmp, term->curs);
		free(tmp);
		tputs(delete_character, 1, my_putchar);
	}
	return (0);
}
