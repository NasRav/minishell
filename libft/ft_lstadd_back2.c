#include "libft.h"

void	ft_lstadd_back2(t_list2 **lst, t_list2 *new)
{
	t_list2	*last;

	last = ft_lstlast2(*lst);
	if (*lst)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}
