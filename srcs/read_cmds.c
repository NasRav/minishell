#include "minishell.h"

static void	add_char(t_term *term, char c)
{
	char			*tmp;
	int				len;
	unsigned int	i;
	unsigned int	j;

	tmp = term->cmd_line->content;
	len = ft_strlen(tmp) + 1;
	term->cmd_line->content = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 2);
	if (!(term->cmd_line->content))
		exit(1);
	i = 0;
	j = 0;
	while (len)
	{
		if (i == term->curs - 1)
			term->cmd_line->content[i] = c;
		else
			term->cmd_line->content[i] = tmp[j++];
		++i;
		--len;
	}
	term->cmd_line->content[i] = 0;
	free(tmp);
}

static char	get_char(t_term *term)
{
	char	c;

	read(0, &c, 1);
	if ((!ft_isprint(c) && c != '\n') || c == '\t')
	{
		if (c == '\3')
			return (ctrl_c(term));
		if (c == '\4' && !term->curs)
			ft_exit(term->history, 0);
		if (c == 127)
			return (backspace(term));
		if (c == '\e')
		{
			read(0, &c, 1);
			read(0, &c, 1);
			if (c == 'A' || c == 'B' || c == 'C' || c == 'D')
				arrow_key_press(term, c);
			return (0);
		}
		return (0);
	}
	++term->curs;
	return (c);
}

static void	read_line(t_term *term)
{
	char	buf[2];

	buf[1] = 0;
	buf[0] = get_char(term);
	while (buf[0] != '\n')
	{
		if (buf[0])
		{
			add_char(term, buf[0]);
			tputs(enter_insert_mode, 1, my_putchar);
			tputs(buf, 1, my_putchar);
			tputs(exit_insert_mode, 1, my_putchar);
		}
		buf[0] = get_char(term);
	}
}

int	get_cmd(t_term *term)
{
	int	rtrn;

	rtrn = 0;
	term->curs = 0;
	term->cmd_line = ft_lstmap2(term->history, ft_strdup, free);
	ft_lstadd_front2(&term->cmd_line, ft_lstnew2(ft_strdup("")));
	term_set(term, 1);
	read_line(term);
	if ((term->cmd_line->content)[0])
	{
		ft_lstadd_front2(&term->history, \
		ft_lstnew2(ft_strdup(term->cmd_line->content)));
		if ((term->cmd_line->content)[0] == '#')
			rtrn = 0;
		else
			rtrn = 1;
	}
	term_set(term, 2);
	ft_lstclear2(&term->cmd_line, free);
	tputs("\n", 1, my_putchar);
	tputs(carriage_return, 1, my_putchar);
	return (rtrn);
}
