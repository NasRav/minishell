#include "libft.h"

void	ft_lstadd_front2(t_list2 **lst, t_list2 *new)
{
	t_list2	*tmp;

	if (new)
	{
		new->next = *lst;
		if (*lst)
		{
			tmp = *lst;
			tmp->prev = new;
		}
		*lst = new;
	}
}
