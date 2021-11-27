#include "minishell.h"

t_list2	*get_history(void)
{
	int		fd;
	int		gnl;
	char	*line;
	t_list2	*history;

	history = 0;
	fd = open(".minish_history", O_RDONLY);
	if (fd < 0)
		return (0);
	gnl = get_next_line(fd, &line);
	while (gnl)
	{
		ft_lstadd_front2(&history, ft_lstnew2(line));
		gnl = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (history);
}

void	save_history(t_list2 **history)
{
	int		fd;
	t_list2	*tmp;

	fd = open(".minish_history", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		exit(2);
	tmp = *history;
	*history = ft_lstlast2(*history);
	while (*history)
	{
		write(fd, (*history)->content, ft_strlen((*history)->content));
		write(fd, "\n", 1);
		*history = (*history)->prev;
	}
	close(fd);
	*history = tmp;
	ft_lstclear2(history, free);
}

void	put_history(t_term *term, char n)
{
	unsigned int	len;

	len = ft_strlen(term->cmd_line->content);
	if (n == 'A' && term->cmd_line->next)
	{
		while (term->curs--)
			tputs(cursor_left, 1, my_putchar);
		while (len--)
			tputs(delete_character, 1, my_putchar);
		term->cmd_line = term->cmd_line->next;
		tputs(term->cmd_line->content, 1, my_putchar);
		term->curs = ft_strlen(term->cmd_line->content);
	}
	else if (n == 'B' && term->cmd_line->prev)
	{
		while (term->curs--)
			tputs(cursor_left, 1, my_putchar);
		while (len--)
			tputs(delete_character, 1, my_putchar);
		term->cmd_line = term->cmd_line->prev;
		tputs(term->cmd_line->content, 1, my_putchar);
		term->curs = ft_strlen(term->cmd_line->content);
	}
}
