#include "libft.h"

void	ft_lstdelone2(t_list2 **lst, void (*del)(void *))
{
	t_list2	*tmp;

	if (!(*lst))
		return ;
	if ((*lst)->prev)
		((*lst)->prev)->next = (*lst)->next;
	if ((*lst)->next)
		((*lst)->next)->prev = (*lst)->prev;
	(*del)((*lst)->content);
	tmp = *lst;
	if ((*lst)->next)
		*lst = (*lst)->next;
	else
		*lst = (*lst)->prev;
	free(tmp);
}
